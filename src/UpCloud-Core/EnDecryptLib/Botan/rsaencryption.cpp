#include "rsaencryption.h"

RSAEncryption::RSAEncryption()
{

}
bool RSAEncryption::encryption(QString &secretKey, QString &plainText, QString &cipherText)
{
    try {
        Botan::LibraryInitializer init;

        std::istringstream read(plainText.toStdString());
        std::ostringstream write;write.clear();write.str("");

        Public_Key* p_PubKey = NULL;
        QFileInfo sourceFileInfo(secretKey);
        if(sourceFileInfo.isFile() == true)
        {
            if(sourceFileInfo.exists() == true)
            {
                //以文件方式加载key
                p_PubKey = X509::load_key(secretKey.toStdString().c_str());
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
            p_PubKey = X509::load_key(source);
        }
        std::auto_ptr<X509_PublicKey> key(p_PubKey);
        RSA_PublicKey* rsakey = dynamic_cast<RSA_PublicKey*>(key.get());
        if(!rsakey)
        {
            qDebug() << "The loaded key is not a RSA key!\n";
            return false;
        }

        AutoSeeded_RNG rng;

        PK_Encryptor_EME encryptor(*rsakey, "EME1(SHA-1)");

        /* Generate the master key (the other keys are derived from this)

             Basically, make the key as large as can be encrypted by this key, up
             to a limit of 256 bits. For 512 bit keys, the master key will be >160
             bits. A >600 bit key will use the full 256 bit master key.

             In theory, this is not enough, because we derive 16+16+8=40 bytes of
             secrets (if you include the IV) using the master key, so they are not
             statistically indepedent. Practically speaking I don't think this is
             a problem.
          */
        SymmetricKey masterkey(rng,
                               std::min<size_t>(32,
                                                encryptor.maximum_input_size()));

        SymmetricKey cast_key = derive_key("CAST", masterkey, 16);
        SymmetricKey mac_key  = derive_key("MAC",  masterkey, 16);
        SymmetricKey iv       = derive_key("IV",   masterkey, 8);

        SecureVector<byte> encrypted_key =
                encryptor.encrypt(masterkey.bits_of(), rng);

        write << b64_encode(encrypted_key) << std::endl;

        Pipe pipe(new Fork(
                      new Chain(
                          get_cipher("CAST-128/CBC/PKCS7", cast_key, iv,
                                     ENCRYPTION),
                          new Base64_Encoder(true) // true == do linebreaking
                          ),
                      new Chain(
                          new MAC_Filter("HMAC(SHA-1)", mac_key, 12),
                          new Base64_Encoder
                          )
                      )
                  );

        pipe.start_msg();
        read >> pipe;
        pipe.end_msg();

        /* Write the MAC as the second line. That way we can pull it off right
             from the start, and feed the rest of the file right into a pipe on the
             decrypting end.
          */

        write << pipe.read_all_as_string(1) << std::endl;
        write << pipe.read_all_as_string(0);
        write.flush();
        cipherText = QString::fromStdString(write.str());
    }
    catch(std::exception& e)
    {
        qDebug() << "Exception: " << e.what();
    }
    return true;
}

std::string RSAEncryption::b64_encode(const SecureVector<byte> &in)
{
    Pipe pipe(new Base64_Encoder);
    pipe.process_msg(in);
    return pipe.read_all_as_string();
}

SymmetricKey RSAEncryption::derive_key(const QString &param, const SymmetricKey &masterkey, quint32 outputlength)
{
    std::auto_ptr<KDF> kdf(get_kdf("KDF2(SHA-1)"));
    return kdf->derive_key(outputlength, masterkey.bits_of(), param.toStdString());
}

