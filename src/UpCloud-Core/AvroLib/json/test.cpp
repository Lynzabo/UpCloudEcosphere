////////////////////////////////////////////////////////////测试一般JSON使用
/*
#include "json.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "person.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
const QString json = QObject::tr("{"
                         "\"encoding\":\"UTF-8\","
                         "\"plug-ins\":[\"python\","
                         "\"c++\",\"ruby\"],"
                         "\"indent\":{"
                              "\"length\":3,"
                              "\"use_space\":true"
                         "}"
                     "}");
void testParse()
{
    bool ok;
    JsonObject result = QtJson::parse(json, ok).toMap();
    if (!ok) {
        qDebug("解析出错");
    }

    qDebug() << "encoding:" << result["encoding"].toString();
    qDebug() << "plugins:";

    JsonArray plugins = result["plug-ins"].toList();
    foreach(QVariant plugin, plugins) {
        qDebug() << "  -" << plugin.toString();
    }

    JsonObject indent = result["indent"].toMap();
    qDebug() << "length:" << indent["length"].toInt();
    qDebug() << "use_space:" << indent["use_space"].toBool();
}
void testParse2()
{
    JsonObject result;
    try
    {
        result = QtJson::parse(json).toMap();
    }
    catch(JsonException &excep)
    {
        qDebug() << excep.getMsg();
    }

    qDebug() << "encoding:" << result["encoding"].toString();
    qDebug() << "plugins:";

    JsonArray plugins = result["plug-ins"].toList();
    foreach(QVariant plugin, plugins) {
        qDebug() << "  -" << plugin.toString();
    }

    JsonObject indent = result["indent"].toMap();
    qDebug() << "length:" << indent["length"].toInt();
    qDebug() << "use_space:" << indent["use_space"].toBool();
}
void testAssembly()
{
    bool ok;
    JsonObject result = QtJson::parse(json, ok).toMap();
    if (!ok) {
        qDebug("解析出错");
    }
    JsonArray keywords = JsonArray() << "json" << "qt" << "parser";
    JsonObject extra;
    extra["ratio"] = 3.35;
    extra["keywords"] = keywords;
    result["extra"] = extra;
    qDebug() << QtJson::serialize(result);
}
void testSerialize()
{
    Person person;
    person.setMyYear(111);
    person.setMyTitle(QString("Tom"));
    person.setMyArtist(QString("Article"));
    JsonObject objJson;
    objJson["myYear"] = person.getMyYear();
    objJson["myArtist"] = person.getMyArtist();
    objJson["myTitle"] = person.getMyTitle();
    qDebug() << QtJson::serialize(objJson);
}
void testSerialize2()
{
    Person person;
    person.setMyYear(111);
    person.setMyTitle(QString("Tom"));
    person.setMyArtist(QString("Article"));
    JsonObject objJson;
    objJson["myYear"] = person.getMyYear();
    objJson["myArtist"] = person.getMyArtist();
    objJson["myTitle"] = person.getMyTitle();
    QByteArray array;
    try
    {
        array = QtJson::serialize(objJson);

    }
    catch(JsonException &excep)
    {
        qDebug() << excep.getMsg();
    }
    qDebug() << array;
}
int main(int argc, char **argv)
{
    ////带返回值输出测试
    //测试反序列化
//    testParse();
    //测试追加
//    testAssembly();
    //测试序列化
    testSerialize();
    ////带异常输出测试
    //测试反序列化
//    testParse2();
//    //测试序列化
//    testSerialize2();
    return 0;
}
*/
////////////////////////////////////////////////////////////测试对象/集合的JSON使用
/*
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "json.h"
#include "person.h"
using QtJson::JsonObject;
using QtJson::JsonArray;

void testMapPOJOToJsonString(QString &coJsonString)
{
    QMap<QString,Person> map;map.clear();
    Person person1("uuid1","name1",(quint16)11,QChar('M'));
    Person person2("uuid2","name2",(quint16)12,QChar('W'));
    Person person3("uuid3","name3",(quint16)13,QChar('M'));
    map.insert(QString("111"),person1);
    map.insert(QString("222"),person2);
    map.insert(QString("333"),person3);
    JsonObject jsonO;
    for(QString key:map.keys())
    {
        Person p = map.value(key);
        JsonObject objJson;
        objJson["uuid"] = p.getUuid();
        objJson["name"] = p.getName();
        objJson["age"] = p.getAge();
        objJson["sex"] = p.getSex();
        QString str = QtJson::serialize(objJson);

        jsonO.insert(key,str);
    }
    coJsonString = QtJson::serialize(jsonO);
    qDebug() << "testMapPOJOToJsonString:\n" << coJsonString;
}
void testMapPOJOFromJsonString(const QString &coJsonString)
{
    bool ok;
    JsonObject result = QtJson::parse(coJsonString, ok).toMap();
    if (!ok) {
        qDebug("解析出错");
        return;
    }
    QMap<QString,Person> map;map.clear();
    for(QString key:result.keys())
    {
        QVariant value = result.value(key);
        JsonObject res = QtJson::parse(value.toString(), ok).toMap();
        if (!ok) {
            qDebug("解析出错");
            return;
        }
        Person person;
        person.setUuid(res["uuid"].toString());
        person.setName(res["name"].toString());
        person.setAge((quint16)(res["age"].toUInt()));
        person.setSex(res["sex"].toChar());
        map.insert(key,person);
    }

    for(QString key:map.keys())
    {
        Person p = map.value(key);
        qDebug() << "key:" << qPrintable(key) << "uuid:" << qPrintable(p.getUuid())
                 << "   name:" << qPrintable(p.getName())
                 << "   age:" << p.getAge()
                 << "   sex:" << p.getSex().toLatin1();
        qDebug("-------");
    }
}

void testMapStrToJsonString(QString &coJsonString)
{
    QMap<QString,QString> map;
    map.insert(QString("11"),QString("111"));
    map.insert(QString("22"),QString("222"));
    map.insert(QString("33"),QString("333"));
    JsonObject objJson;
    for(QString key:map.keys())
    {
        objJson.insert(key,map.value(key));
    }
    coJsonString = QtJson::serialize(objJson);
    qDebug() << "testMapStrToJsonString:\n" << coJsonString;
}
void testMapStrFromJsonString(const QString &coJsonString)
{
    bool ok;
    JsonObject result = QtJson::parse(coJsonString, ok).toMap();
    if (!ok) {
        qDebug("解析出错");
        return;
    }
    QMap<QString,QString> map;
    for(QString key:result.keys())
    {
        map.insert(key,result[key].toString());
    }
    for(QString key:map.keys())
    {
        QString val = map.value(key);
        qDebug() << key << ":" << qPrintable(val);
    }
}

void testListPOJOToJsonString(QString &coJsonString)
{
    Person person1("uuid1","name1",(quint16)11,QChar('M'));
    Person person2("uuid2","name2",(quint16)12,QChar('W'));
    Person person3("uuid3","name3",(quint16)13,QChar('M'));
    QList<Person> list;list.clear();
    list.append(person1);
    list.append(person2);
    list.append(person3);


    JsonArray jsonArray;
    for(Person p:list)
    {
        JsonObject objJson;
        objJson["uuid"] = p.getUuid();
        objJson["name"] = p.getName();
        objJson["age"] = p.getAge();
        objJson["sex"] = p.getSex();
        QString str = QtJson::serialize(objJson);
        jsonArray = jsonArray << str;
    }
    coJsonString = QtJson::serialize(jsonArray);
    qDebug() << "testListPOJOToJsonString:\n" << coJsonString;
}
void testListPOJOFromJsonString(const QString &coJsonString)
{
    bool ok;
    JsonArray array = QtJson::parse(coJsonString, ok).toList();
    if (!ok) {
        qDebug("解析出错");
        return;
    }
    QList<Person> list;list.clear();
    qDebug() << "testListPOJOFromJsonString:";
    for(QVariant var:array)
    {
        JsonObject result = QtJson::parse(var.toString(), ok).toMap();
        if (!ok) {
            qDebug("解析出错");
            return;
        }
        Person person;
        person.setUuid(result["uuid"].toString());
        person.setName(result["name"].toString());
        person.setAge((quint16)(result["age"].toUInt()));
        person.setSex(result["sex"].toChar());
        list.append(person);
    }
    for(Person p:list)
    {
        qDebug() << "uuid:" << qPrintable(p.getUuid());
        qDebug() << "name:" << qPrintable(p.getName());
        qDebug() << "age:" << p.getAge();
        qDebug() << "sex:" << p.getSex().toLatin1();
        qDebug("-------");
    }
}

void testListStrToJsonString(QString &coJsonString)
{
    QList<QString> list;list.clear();
    list.append(QString("name1"));
    list.append(QString("name2"));
    list.append(QString("name3"));


    JsonArray jsonArray;
    for(QString p:list)
    {
        jsonArray = jsonArray << p;
    }
    coJsonString = QtJson::serialize(jsonArray);
    qDebug() << "testListStrToJsonString:\n" << coJsonString;
}
void testListStrFromJsonString(const QString &coJsonString)
{
    bool ok;
    JsonArray array = QtJson::parse(coJsonString, ok).toList();
    if (!ok) {
        qDebug("解析出错");
        return;
    }
    QList<QString> list;list.clear();
    qDebug() << "testListStrFromJsonString:";
    for(QVariant var:array)
    {
        list.append(var.toString());
    }
    for(QString p:list)
    {
        qDebug() << qPrintable(p);
        qDebug("-------");
    }
}
void testCommonPOJOToJsonString(QString &coJsonString)
{
    Person *person = new Person("uuid1","name1",(quint16)10,QChar('M'));
    JsonObject objJson;
    objJson["uuid"] = person->getUuid();
    objJson["name"] = person->getName();
    objJson["age"] = person->getAge();
    objJson["sex"] = person->getSex();

    coJsonString = QtJson::serialize(objJson);
    qDebug() << "testCommonPOJOToJsonString:\n" << coJsonString;
    delete person;
}
void testCommonPOJOFromJsonString(const QString &coJsonString)
{
    bool ok;
    JsonObject result = QtJson::parse(coJsonString, ok).toMap();
    if (!ok) {
        qDebug("解析出错");
        return;
    }
    Person *person = new Person;
    person->setUuid(result["uuid"].toString());
    person->setName(result["name"].toString());
    person->setAge((quint16)(result["age"].toUInt()));
    person->setSex(result["sex"].toChar());
    qDebug() << "testCommonPOJOFromJsonString:";
    qDebug() << "uuid:" << qPrintable(person->getUuid());
    qDebug() << "name:" << qPrintable(person->getName());
    qDebug() << "age:" << person->getAge();
    qDebug() << "sex:" << person->getSex().toLatin1();
    delete person;
}
int main(int argc, char **argv)
{
    /*
    qDebug() << "\nTest Person--------";
    QString coJsonString;coJsonString.clear();
    //测试对象序列化成JSON字符串
    testCommonPOJOToJsonString(coJsonString);
    //将JSON字符串反序列化成对象
    testCommonPOJOFromJsonString(coJsonString);
    */
    /*
    qDebug() << "\nTest QList<QString>--------";
    QString lpsJsonString;lpsJsonString.clear();
    testListStrToJsonString(lpsJsonString);
    testListStrFromJsonString(lpsJsonString);
    */
    /*
    qDebug() << "\nTest QList<Person>--------";
    QString lpJsonString;lpJsonString.clear();
    (lpJsonString);
    testListPOJOFromJsonString(lpJsonString);
    */
    /*
    qDebug() << "\nTest QMap<quint16,QString>--------";
    QString lmJsonString;lmJsonString.clear();
    testMapStrToJsonString(lmJsonString);
    testMapStrFromJsonString(lmJsonString);
    */
    /*
    qDebug() << "\nTest QMap<QString,Person>--------";
    QString lmpJsonString;lmpJsonString.clear();
    testMapPOJOToJsonString(lmpJsonString);
    testMapPOJOFromJsonString(lmpJsonString);
    */
    /*
    //方法和上面类似,就是把上面QList<Person>的字符串作为map的value就行
    qDebug() << "\nTest QMap<String,QList<Person>>--------";
    */
    /*
    //方法和上面类似,就是把上面QMap<String,Person>的字符串作为map的value就行
    qDebug() << "\nTest QMap<String,QMap<String,Person>>--------";
    */
    //复杂,上面复杂+自定义key-value
    /*return 0;
}
*/
