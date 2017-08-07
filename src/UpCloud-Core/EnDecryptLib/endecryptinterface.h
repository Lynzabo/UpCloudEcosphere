#ifndef ENDECRYPTINTERFACE
#define ENDECRYPTINTERFACE
#include <QtCore>
#include "endecryptlib_global.h"
class ENDECRYPTLIBSHARED_EXPORT EnDecryptInterface
{
    /**
     * @brief generateKey 生成密钥
     * @param keySize   密钥长度
     * @param pubKey    生成的公钥
     * @param priKey    生成的私钥
     * @return  如果生成成功返回true, 失败返回false
     */
    virtual bool generateKey(quint32 keySize,
                     QString& pubKey,
                     QString& priKey) = 0;

    /**
     * @brief encryption    执行加密操作
     * @param secretKey     密钥[可以是全路径文件名如：c:/test/pub.ke,  也可以是字符串]
     * @param plainText     明文
     * @param cipherText    密文
     * @return  如果加密成功返回true, 失败返回false
     */
    virtual bool encryption(QString& secretKey,
                    QString& plainText,
                    QString& cipherText) = 0;


    /**
     * @brief decryption    执行解密操作
     * @param secretKey     密钥[可以是全路径文件名如：c:/test/pub.ke,  也可以是字符串]
     * @param cipherText    密文
     * @param plainText     明文
     * @param passphrase    解密口令
     * @return              如果解密成功返回true, 失败返回false
     */
    virtual bool decryption(QString& secretKey,
                    QString& cipherText,
                    QString& plainText,
                    QString passphrase = QString()) = 0;
};
#endif // ENDECRYPTINTERFACE

