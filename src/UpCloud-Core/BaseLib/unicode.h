/**
*
*
*                        _oo0oo_
*                       o8888888o
*                       88" . "88
*                       (| -_- |)
*                       0\  =  /0
*                     ___/`---'\___
*                   .' \\|     |// '.
*                  / \\|||  :  |||// \
*                 / _||||| -:- |||||- \
*                |   | \\\  -  * / |   |
*                | \_|  ''\---/''  |_/ |
*                \  .-\__  '-'  ___/-. /
*              ___'. .'  /--.--\  `. .'___
*           ."" '<  `.___\_<|>_/___.' >' "".
*          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
*          \  \ `_.   \_ __\ /__ _/   .-` /  /
*      =====`-.____`.___ \_____/___.-`___.-'=====
*                        `=---='
*
*
*      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*                佛祖保佑         永无BUG
*                心外无法         法外无心
*		佛曰:
*              写字楼里写字间，写字间里程序员；
*              程序人员写程序，又拿程序换酒钱。
*              酒醒只在网上坐，酒醉还来网下眠；
*              酒醉酒醒日复日，网上网下年复年。
*              但愿老死电脑间，不愿鞠躬老板前；
*              奔驰宝马贵者趣，公交自行程序员。
*              别人笑我忒疯癫，我笑自己命太贱；
*              不见满街漂亮妹，哪个归得程序员？
*
*  Module Desc: 生态圈常量配置
*  User: Lynzabo || lzb_178@163.com
*  Date: 2015/7/21
*  Time: 14:27
*/
#ifndef UNICODE_H
#define UNICODE_H
#include "baselib_global.h"
#include <QTextCodec>
#ifdef Q_OS_WIN
#define trs(STR) Unicode::codec_GBK->toUnicode((STR)) //Unicodec tr marco for QT5
#else
#define trs(STR) Unicode::codec_UTF8->toUnicode((STR)) //Unicodec tr marco for QT5
#endif
//#define trs(STR) QCoreApplication::translate("", STR, 0); //Unicodec tr marco for QT5
class BASELIBSHARED_EXPORT Unicode
{
public:
    static QTextCodec *codec_GBK;
    static QTextCodec *codec_UTF8;
public:
    Unicode();
};

#endif // UNICODE_H
