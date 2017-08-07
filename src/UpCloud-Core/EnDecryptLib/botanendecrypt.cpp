#include "botanendecrypt.h"
#include "Botan/rsageneratekey.h"
#include "Botan/rsaencryption.h"
#include "Botan/rsadecryption.h"
QReadWriteLock lock;
BotanEnDecrypt::BotanEnDecrypt()
{
    m_genKey = new RSAGenerateKey;
    m_encrypt = new RSAEncryption;
    m_decrypt = new RSADecryption;
}

BotanEnDecrypt::~BotanEnDecrypt()
{
    if(m_genKey != NULL)
    {
        delete m_genKey;
        m_genKey = NULL;
    }
    if(m_encrypt != NULL)
    {
        delete m_encrypt;
        m_encrypt = NULL;
    }
    if(m_decrypt != NULL)
    {
        delete m_decrypt;
        m_decrypt = NULL;
    }
}

bool BotanEnDecrypt::generateKey(quint32 keySize, QString &pubKey, QString &priKey)
{
    bool ok;
    lock.lockForWrite();
    ok = m_genKey->generateKey(keySize, pubKey, priKey);
    lock.unlock();
    return ok;
}

bool BotanEnDecrypt::encryption(QString &secretKey, QString &plainText, QString &cipherText)
{
    bool ok;
    lock.lockForWrite();
    ok = m_encrypt->encryption(secretKey, plainText, cipherText);
    lock.unlock();
    return ok;
}

bool BotanEnDecrypt::decryption(QString &secretKey, QString &cipherText, QString &plainText, QString passphrase)
{
    bool ok;
    lock.lockForWrite();
    ok = m_decrypt->decryption(secretKey, cipherText, plainText, passphrase);
    lock.unlock();
    return ok;
}

