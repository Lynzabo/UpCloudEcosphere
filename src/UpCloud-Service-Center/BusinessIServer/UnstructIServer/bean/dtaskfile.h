#ifndef DTASKFILE_H
#define DTASKFILE_H

#include <QtCore>

class DTaskFile
{
public:
    DTaskFile();

    QString getFileName() const;
    void setFileName(const QString &value);

    QString getSrcAbst() const;
    void setSrcAbst(const QString &value);

    QString getFileDestName() const;
    void setFileDestName(const QString &value);

    QString getSaveAbst() const;
    void setSaveAbst(const QString &value);

private:
    QString fileName;
    QString srcAbst;
    QString fileDestName;
    QString saveAbst;

};

#endif // DTASKFILE_H
