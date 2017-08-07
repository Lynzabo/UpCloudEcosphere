#ifndef RSAGENERATEKEY_H
#define RSAGENERATEKEY_H

#include <QtCore>

#include <botan/botan.h>
#include <botan/pubkey.h>
#include <botan/rsa.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace Botan;

class  RSAGenerateKey
{
public:
    RSAGenerateKey();   

    /**
     * @brief generateKey 生成密钥
     * @param keySize   密钥长度
     * @param pubKey    生成的公钥
     * @param priKey    生成的私钥
     * @return  如果生成成功返回true, 失败返回false
     */
    bool generateKey(quint32 keySize, QString& pubKey, QString& priKey);

};

#endif // RSAGENERATEKEY_H
