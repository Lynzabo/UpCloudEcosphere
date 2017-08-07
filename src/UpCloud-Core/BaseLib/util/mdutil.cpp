#include "mdutil.h"
SINGLETON_ALL_IN_ONE(MdUtil)
void MdUtil::toMd5(const QString &src, QString &md5desc)
{
    md5desc.clear();
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(src);
    md.addData(ba);
    bb = md.result();
    md5desc.append(bb.toHex());
}
