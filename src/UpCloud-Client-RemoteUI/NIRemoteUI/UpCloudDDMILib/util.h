#ifndef UTIL
#define UTIL
#include "jni.h"
#include <QtCore>
/**
 * @brief jstringTostring   jstring转char*
 * @param env
 * @param jstr
 * @return
 */
char* jstringTostring(JNIEnv* env, jstring jstr);
/**
 * @brief stoJstring    char*转jstring
 * @param env
 * @param pat
 * @return
 */
jstring stoJstring(JNIEnv* env, const char* pat);
#endif // UTIL

