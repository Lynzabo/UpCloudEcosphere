#ifndef JSON_H
#define JSON_H
#include <QVariant>
#include <QString>
#include "avrolib_global.h"
#include "excep/jsonexception.h"
#include "base.h"
/**
 *  JSON格式序列化/反序列化数据
 * JSON数据到QVariant结构映射
 */
namespace QtJson {
    typedef QVariantMap JsonObject;
    typedef QVariantList JsonArray;
    /**
     * @brief parse 解析JSON字符串,附带解析状态
     * @param json
     * @return
     * @throws   JsonException
     */
    AVROLIBSHARED_EXPORT QVariant parse(const QString &json);
    /**
     * @brief parse 解析JSON字符串,附带解析状态
     * @param json
     * @param success
     * @return
     */
    AVROLIBSHARED_EXPORT QVariant parse(const QString &json, bool &success);

    /**
     * @brief serialize 生成JSON串QByteArray
     * @param data
     * @return  JSON串按UTF-8生成QByteArray
     * @throws   JsonException
     */
    AVROLIBSHARED_EXPORT QByteArray serialize(const QVariant &data);

    /**
     * @brief serialize 生成JSON串QByteArray,附带生成状态
     * @param data
     * @return  JSON串按UTF-8生成QByteArray
     */
    AVROLIBSHARED_EXPORT QByteArray serialize(const QVariant &data, bool &success);

    /**
     * @brief serializeStr 生成JSON串
     * @param data
     * @return
     * @throws   JsonException
     */
    AVROLIBSHARED_EXPORT QString serializeStr(const QVariant &data);

    /**
     * @brief serializeStr  生成JSON串,附带生成状态
     * @param data
     * @param success
     * @return
     */
    AVROLIBSHARED_EXPORT QString serializeStr(const QVariant &data, bool &success);

    //声明内部使用函数                  不对外开放                                                begin
    /**
     * @brief setDateTimeFormat 格式化时间为QDateTime::toString格式
     * @param format
     */
    void setDateTimeFormat(const QString& format);
    /**
     * @brief setDateFormat 格式化日期为QDateTime::toString
     * @param format
     */
    void setDateFormat(const QString& format);
    QString getDateTimeFormat();
    QString getDateFormat();
    //声明内部使用函数                  不对外开放                                                end
}

#endif // JSON_H
