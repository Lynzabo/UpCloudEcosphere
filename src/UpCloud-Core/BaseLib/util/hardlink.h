#ifndef HARDLINK_H
#define HARDLINK_H

#include <QtCore>
#include "baselib_global.h"

#ifdef Q_OS_WIN
#define _WIN32_WINNT 0x500
#include <Windows.h>
#include "WinBase.h"
#else
#include "unistd.h"
#endif

class BASELIBSHARED_EXPORT HardLink
{
public:
    HardLink();
    /**
     * @brief creatFileHardLink
     * @param sourceFilePath
     * @param descFilePath
     * @return 成功返回0， 失败返回-1
     */
    static int creatFileHardLink(const QString& sourceFilePath, const QString& descFilePath);
    /**
     * @brief deleteFileHardLink
     * @param filePath
     * @return 成功返回0， 失败返回-1
     */
    static int deleteFileHardLink(const QString& filePath);
};

#endif // HARDLINK_H
