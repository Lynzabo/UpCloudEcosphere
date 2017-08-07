#ifndef RSADECRYPTION_H
#define RSADECRYPTION_H

#include <QtCore>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <botan/botan.h>
#include <botan/pubkey.h>
#include <botan/rsa.h>
#include <botan/base64.h>

using namespace Botan;

class  RSADecryption
{
public:
    RSADecryption();

    /**
     * @brief decryption    执行解密操作
     * @param secretKey     密钥
     * @param cipherText    密文
     * @param plainText     明文
     * @param passphrase    解密口令
     * @return              如果解密成功返回true, 失败返回false
     */
    bool decryption(QString& secretKey,
                    QString& cipherText,
                    QString& plainText,
                    QString passphrase = QString());    

private:
    SecureVector<byte> b64_decode(const std::string& in);
    SymmetricKey derive_key(const QString& param, const SymmetricKey& masterkey, quint32 outputlength);

};

#endif // RSADECRYPTION_H
