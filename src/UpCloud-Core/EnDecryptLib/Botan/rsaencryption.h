#ifndef RSAENCRYPTION_H
#define RSAENCRYPTION_H

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


class  RSAEncryption
{
public:
    RSAEncryption();

    /**
     * @brief encryption    执行加密操作
     * @param secretKey     密钥
     * @param plainText     明文
     * @param cipherText    密文
     * @return  如果加密成功返回true, 失败返回false
     */
    bool encryption(QString& secretKey,
                    QString& plainText,
                    QString& cipherText);

private:

    std::string b64_encode(const SecureVector<Botan::byte> &in);
    SymmetricKey derive_key(const QString& param, const SymmetricKey& masterkey, quint32 outputlength);
};

#endif // RSAENCRYPTION_H
