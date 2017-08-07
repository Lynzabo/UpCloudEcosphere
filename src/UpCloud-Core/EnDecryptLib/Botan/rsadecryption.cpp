#include "rsadecryption.h"

RSADecryption::RSADecryption()
{

}

bool RSADecryption::decryption(QString &secretKey,
                               QString &cipherText,
                               QString &plainText,
                               QString  passphrase)
{
    try
    {
        Botan::LibraryInitializer init;

        AutoSeeded_RNG rng;

        Private_Key* p_PriKey= NULL;
        QFileInfo sourceFileInfo(secretKey);
        if(sourceFileInfo.isFile() == true)
        {
            if(sourceFileInfo.exists() == true)
            {
                //以文件方式加载key
                p_PriKey = PKCS8::load_key(secretKey.toStdString().c_str(),
                                         rng,
                                         passphrase.toStdString().c_str());
            }
            else
            {
                qDebug() << "sourceFile:" << secretKey << " is not exists!";
                return false;
            }
        }
        else
        {
            //以String字符串方式加载Key
            DataSource_Memory source(secretKey.toStdString());
            p_PriKey = PKCS8::load_key(source,
                                     rng,
                                     passphrase.toStdString().c_str());
        }

        std::auto_ptr<PKCS8_PrivateKey> key(p_PriKey);
        RSA_PrivateKey* rsakey = dynamic_cast<RSA_PrivateKey*>(key.get());
        if(!rsakey)
        {
            qDebug() << "The loaded key is not a RSA key!\n";
            return false;
        }
        std::istringstream read(cipherText.toStdString());
        std::ostringstream write;write.clear();write.str("");

        std::string enc_masterkey_str;
        std::getline(read, enc_masterkey_str);
        std::string mac_str;
        std::getline(read, mac_str);
        mac_str = QString::fromStdString(mac_str).trimmed().toStdString();

        SecureVector<byte> enc_masterkey = b64_decode(enc_masterkey_str);

        PK_Decryptor_EME decryptor(*rsakey, "EME1(SHA-1)");

        SecureVector<byte> masterkey = decryptor.decrypt(enc_masterkey);

        SymmetricKey cast_key   = derive_key("CAST", masterkey, 16);
        InitializationVector iv = derive_key("IV",   masterkey, 8);
        SymmetricKey mac_key    = derive_key("MAC",  masterkey, 16);

        Pipe pipe(new Base64_Decoder,
                  get_cipher("CAST-128/CBC/PKCS7", cast_key, iv, DECRYPTION),
                  new Fork(
                      0,
                      new Chain(
                          new MAC_Filter("HMAC(SHA-1)", mac_key, 12),
                          new Base64_Encoder
                          )
                      )
                  );

        pipe.start_msg();
        read >> pipe;
        pipe.end_msg();

        std::string our_mac = pipe.read_all_as_string(1);

        if(our_mac != mac_str)
            qDebug() << "WARNING: MAC in message failed to verify";

        write << pipe.read_all_as_string(0);
        write.flush();
        plainText = QString::fromStdString(write.str());
    }
    catch(std::exception& e)
    {
        qDebug() << "Exception caught: " << e.what();
        return false;
    }
    return true;
}


SecureVector<byte> RSADecryption::b64_decode(const std::string &in)
{
    Pipe pipe(new Base64_Decoder);
    pipe.process_msg(in);
    return pipe.read_all();
}



SymmetricKey RSADecryption::derive_key(const QString &param, const SymmetricKey &masterkey, quint32 outputlength)
{
    std::auto_ptr<KDF> kdf(get_kdf("KDF2(SHA-1)"));
    return kdf->derive_key(outputlength, masterkey.bits_of(), param.toStdString());
}

