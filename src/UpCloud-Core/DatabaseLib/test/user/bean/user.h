#ifndef USER_H
#define USER_H

#include <QString>
#include "databaselib_global.h"

class DATABASELIBSHARED_EXPORT User {
public:
    User();

    int id;
    QString username;
    QString password;
    QString email;
    QString mobile;

    QString toString() const;
};

#endif // USER_H
