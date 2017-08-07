#include "rsageneratekey.h"

RSAGenerateKey::RSAGenerateKey()
{

}


bool RSAGenerateKey::generateKey(quint32 keySize, QString &pubKey, QString &priKey)
{
    if(keySize < 1024 || keySize > 16384)
    {
        qDebug() << "Invalid argument for keySize";
        return false;
    }
    pubKey.clear();
    priKey.clear();

    try
    {
        Botan::LibraryInitializer init;

        AutoSeeded_RNG rng;
        RSA_PrivateKey key(rng, keySize);

        pubKey = QString::fromStdString(X509::PEM_encode(key));
        priKey = QString::fromStdString(PKCS8::PEM_encode(key));
    }
    catch(std::exception& e)
    {
        qDebug() << "Exception caught: " << e.what();

        return false;
    }
    return true;
}

