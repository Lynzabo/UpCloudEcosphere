/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni.h"
#include "upcloudddmilib_global.h"
/* Header for class com_upcloud_ddmi_core_DDEditor */
#include "base.h"
#include "duplex.h"
#include "baseiremote.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtask.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskaddr.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/dtaskfile.h"

#include "../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h"
#ifndef _Included_com_upcloud_ddmi_core_DDEditor
#define _Included_com_upcloud_ddmi_core_DDEditor
#ifdef __cplusplus
extern "C" {
#endif
enum LogLevel {
    D,
    I,
    E,
    F
};
/*
 * Class:     com_upcloud_ddmi_core_DDEditor
 * Method:    doSend
 * Signature: ()[Ljava/lang/String;
 */
UPCLOUDDDMILIBSHARED_EXPORT JNIEXPORT jobjectArray JNICALL Java_com_upcloud_ddmi_core_DDEditor_doSend
(JNIEnv *env, jobject obj);

/*
 * Class:     com_upcloud_ddmi_core_DDEditor
 * Method:    doDelete
 * Signature: ()[Ljava/lang/String;
 */
UPCLOUDDDMILIBSHARED_EXPORT JNIEXPORT jobjectArray JNICALL Java_com_upcloud_ddmi_core_DDEditor_doDelete
(JNIEnv *env, jobject obj);


/*
 * Class:     com_upcloud_ddmi_core_DDEditor
 * Method:    doDelete
 * Signature: ([Ljava/lang/String;)V
 */
/*
UPCLOUDDDMILIBSHARED_EXPORT JNIEXPORT void JNICALL Java_com_upcloud_ddmi_core_DDEditor_doDelete
(JNIEnv *env, jobject obj, jobjectArray uuids);
*/
/*
 * Class:     com_upcloud_ddmi_core_DDEditor
 * Method:    doCommit
 * Signature: ()V
 */
UPCLOUDDDMILIBSHARED_EXPORT JNIEXPORT void JNICALL Java_com_upcloud_ddmi_core_DDEditor_doCommit
  (JNIEnv *env, jobject obj);

/*
 * Class:     com_upcloud_ddmi_core_DDEditor
 * Method:    doRollback
 * Signature: ()V
 */
UPCLOUDDDMILIBSHARED_EXPORT JNIEXPORT void JNICALL Java_com_upcloud_ddmi_core_DDEditor_doRollback
  (JNIEnv *env, jobject obj);



void getTaskInfo(JNIEnv *env, jobject ddEditor_obj,DTask &task);
void getTaskAddrs(JNIEnv *env, jobject ddEditor_obj,QList<DTaskAddr> &addrsList);
void getTaskUnstructFiles(JNIEnv *env, jobject ddEditor_obj,QList<DTaskFile> &uFilesList);
void getTaskStructFiles(JNIEnv *env, jobject ddEditor_obj,QList<DTaskFile> &sFilesList);
void output(JNIEnv *env, const QString &msg = QString(), const LogLevel &logLevel = LogLevel::D);
#ifdef __cplusplus
}
#endif
#endif
