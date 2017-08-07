#include "com_upcloud_ddmi_core_DDEditor.h"
#include <QtCore>
#include <iostream>
using namespace Environment::Datagram::Web_Serverlet::DDEditor;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;

JNIEXPORT jobjectArray JNICALL Java_com_upcloud_ddmi_core_DDEditor_doSend
(JNIEnv *env, jobject obj)
{
    //[0]返回值 及 异常
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray retArray = env->NewObjectArray(2, stringClass, 0);
    QString uTaskUUID; uTaskUUID.clear();
    QString sTaskUUID; sTaskUUID.clear();

    QString exMsg; exMsg.clear();

    ////[1]生成任务实体
    DTask task;
    getTaskInfo(env,obj,task);

    ////[2]生成地址列表实体
    QList<DTaskAddr> addrsList;
    addrsList.clear();
    getTaskAddrs(env,obj,addrsList);

    ////[3]生成非结构化文件列表实体
    QList<DTaskFile> uFilesList;
    uFilesList.clear();
    getTaskUnstructFiles(env,obj,uFilesList);

    ////[4]生成结构化文件列表实体
    QList<DTaskFile> sFilesList;
    sFilesList.clear();
    getTaskStructFiles(env,obj,sFilesList);

    ////[5]发送消息
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    QString params;params.clear();
    UnstructUtil::DTaskDDEditorEntityToJsonStr(task, addrsList, uFilesList, sFilesList, params);

    sender->setExecType(Opera_Type::Task_send);
    sender->setParams(params);

    DPResult* resultSet = sender->doSendBySync();

    ////[6]反馈结果集
    quint8 rState;
    QString result;result.clear();

    rState = resultSet->getRState();
    result = resultSet->getRContent();

    ////[6].1通用校验
    //消息ID
    qint32 cbMsgId;cbMsgId = 0;
    //消息内容
    QString cbMsg;cbMsg.clear();
    //地址无效
    if(rState == Data_Authority::_2) {
        qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
        cbMsgId = CallbackStatus::Unstruct::_1;
        cbMsg = CallbackStatus::Unstruct::_1_Desc_AddrIsInvalid;
        exMsg = cbMsg;
        goto ERRORs;
    }
    //未授权访问
    else if(rState == Data_Authority::_1) {
        qDebug() << Data_Authority::_1_DESC_Unauthorized;
        cbMsgId = CallbackStatus::Unstruct::_2;
        cbMsg = CallbackStatus::Unstruct::_2_Desc_Unauthorized;
        exMsg = cbMsg;
        goto ERRORs;
    }
    //数据库操作失败
    else if(rState == Data_Authority::_4) {
        qDebug() << Data_Authority::_4_DESC_DatabaseError;
        cbMsgId = CallbackStatus::Unstruct::_3;
        cbMsg = CallbackStatus::Unstruct::_3_Desc_DatabaseError;
        exMsg = cbMsg;
        goto ERRORs;
    }
    //解析参数失败
    else if(rState == Data_Authority::_5) {
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        cbMsgId = CallbackStatus::Unstruct::_4;
        cbMsg = CallbackStatus::Unstruct::_4_Desc_ParamParseError;
        exMsg = cbMsg;
        goto ERRORs;
    }
    //没有可下发的节点服务器
    else if(rState == Data_Authority::_6) {
        qDebug() << Data_Authority::_6_DESC_NoderIsNull;
        cbMsgId = CallbackStatus::Unstruct::_5;
        cbMsg = CallbackStatus::Unstruct::_5_Desc_SeiviceIsNull;
        exMsg = cbMsg;
        goto ERRORs;
    }
    //解析返回数据失败
    else if(rState == Data_Authority::_8) {
        qDebug() << Data_Authority::_8_DESC_ParseDataError;
        cbMsgId = CallbackStatus::Unstruct::_6;
        cbMsg = CallbackStatus::Unstruct::_6_Desc_ParseDataError;
        exMsg = cbMsg;
        goto ERRORs;
    }

    ////[6].2自定义校验 服务端获取参数为空
    else if(rState == Data_Authority::_7) {
        qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
        cbMsgId = CallbackStatus::Unstruct::_7;
        cbMsg = CallbackStatus::Unstruct::_7_Desc_ParamsHasNullValue;
        exMsg = cbMsg;
        goto ERRORs;
    }
    //操作成功
    else if(rState == Data_Authority::_0)
    {
        bool isSuccess;
        JsonObject jsonResult = QtJson::parse(result,isSuccess).toMap();
        if(isSuccess)
        {
            uTaskUUID = jsonResult["UTaskUUID"].toString();
            sTaskUUID = jsonResult["STaskUUID"].toString();

            jstring str;
            str = env->NewStringUTF(uTaskUUID.toStdString().c_str());
            env->SetObjectArrayElement(retArray,0, str);

            str = env->NewStringUTF(sTaskUUID.toStdString().c_str());
            env->SetObjectArrayElement(retArray,1, str);

            sender->destory();
            return retArray;
        }
        else
        {
            exMsg = QString("Parse result data error!");
            goto ERRORs;
        }
    }
ERRORs:
    sender->destory();
    jclass ddEditExcepCls = env->FindClass("com/upcloud/ddmi/core/exception/DDMIEditException");
    env->ThrowNew(ddEditExcepCls,qPrintable(trs(exMsg.toStdString().c_str())));
}

//doDelete String[] fun();
JNIEXPORT jobjectArray JNICALL Java_com_upcloud_ddmi_core_DDEditor_doDelete
(JNIEnv *env, jobject obj)
{
    //TODO 目前只是定义了返回值使得编译通过
    //[0]返回值 及 异常
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray retArray = env->NewObjectArray(2, stringClass, 0);
    QString uTaskUUID; uTaskUUID.clear();
    QString sTaskUUID; sTaskUUID.clear();


    uTaskUUID = QString("22222222222222222222222222222222");
    sTaskUUID = QString("33333333333333333333333333333333");

    jstring str;
    str = env->NewStringUTF(uTaskUUID.toStdString().c_str());
    env->SetObjectArrayElement(retArray,0, str);

    str = env->NewStringUTF(sTaskUUID.toStdString().c_str());
    env->SetObjectArrayElement(retArray,1, str);

    return retArray;
}
/*
//doDelete void fun();
JNIEXPORT void JNICALL Java_com_upcloud_ddmi_core_DDEditor_doDelete
(JNIEnv *env, jobject obj, jobjectArray uuids)
{
//    QString uTaskUUID;uTaskUUID.clear();
//    QString sTaskUUID;sTaskUUID.clear();
//    //获取数组宽度
//    //    int length = env->GetArrayLength(uuids);
//    jstring j_uuid = (jstring)env->GetObjectArrayElement(uuids,0);
//    const char* c_uuid = env->GetStringUTFChars(j_uuid,NULL);
//    uTaskUUID = QString(c_uuid);
//    env->ReleaseStringUTFChars(j_uuid,c_uuid);
//    jstring j_uuid2 = (jstring)env->GetObjectArrayElement(uuids,1);
//    const char* c_uuid2 = env->GetStringUTFChars(j_uuid2,NULL);
//    sTaskUUID = QString(c_uuid2);
//    env->ReleaseStringUTFChars(j_uuid2,c_uuid2);
//    output(env,uTaskUUID,LogLevel::D);
//    output(env,sTaskUUID,LogLevel::D);

}
*/
//commit
void Java_com_upcloud_ddmi_core_DDEditor_doCommit(JNIEnv *env, jobject obj)
{

}

//rollback
void Java_com_upcloud_ddmi_core_DDEditor_doRollback(JNIEnv *env, jobject obj)
{

}

//[1]生成任务实体
void getTaskInfo(JNIEnv *env, jobject ddEditor_obj, DTask &task)
{
    jclass ddEditor_clazz = env->GetObjectClass(ddEditor_obj);
    //获取任务信息
    QString taskName;taskName.clear();
    QString description;description.clear();
    short strategy;strategy = 0;

    jfieldID fieldID_dtask = env->GetFieldID(ddEditor_clazz,"dtask","Lcom/upcloud/ddmi/core/dto/Task;");
    jobject obj_dtask = env->GetObjectField(ddEditor_obj,fieldID_dtask);
    jclass task_clazz = env->GetObjectClass(obj_dtask);

    //获取任务名称 taskName
    jfieldID fieldID_taskName = env->GetFieldID(task_clazz,"taskName","Ljava/lang/String;");
    jstring j_taskName = (jstring)env->GetObjectField(obj_dtask,fieldID_taskName);
    const char* c_taskName = env->GetStringUTFChars(j_taskName,NULL);
    taskName = QString(c_taskName);
    env->ReleaseStringUTFChars(j_taskName,c_taskName);

    //获取任务描述 description
    jfieldID fieldID_description = env->GetFieldID(task_clazz,"description","Ljava/lang/String;");
    jstring j_description = (jstring)env->GetObjectField(obj_dtask,fieldID_description);
    const char* c_description = env->GetStringUTFChars(j_description,NULL);
    description = QString(c_description);
    env->ReleaseStringUTFChars(j_description,c_description);

    //获取下发策略 strategy
    jfieldID fieldID_strategy = env->GetFieldID(task_clazz,"strategy","S");
    jshort j_strategy = env->GetShortField(obj_dtask,fieldID_strategy);
    strategy = j_strategy;


    //生成任务实体
    task.setTaskName(taskName);
    task.setDescription(description);
    task.setStrategy((quint16)strategy);
}

//[2]生成地址列表实体
void getTaskAddrs(JNIEnv *env, jobject ddEditor_obj, QList<DTaskAddr> &addrsList)
{
    addrsList.clear();

    jclass ddEditor_clazz = env->GetObjectClass(ddEditor_obj);
    jfieldID fieldID_daddrs = env->GetFieldID(ddEditor_clazz,"daddrs","Ljava/util/List;");
    jobject obj_daddrs = env->GetObjectField(ddEditor_obj,fieldID_daddrs);
    jclass clazz_daddrs = env->GetObjectClass(obj_daddrs);
    jmethodID jm_size = env->GetMethodID(clazz_daddrs,"size","()I");

    //获取daddrs大小
    jint size = env->CallIntMethod(obj_daddrs,jm_size);

    QString addrUUID;addrUUID.clear();
    bool isGroup;isGroup = false;
    for(jint index = 0; index <size; index++)
    {
        //TaskAddr对象j_taskAddr
        addrUUID.clear();
        isGroup = false;

        jmethodID jm_get = env->GetMethodID(clazz_daddrs,"get","(I)Ljava/lang/Object;");
        jobject j_taskAddr = env->CallObjectMethod(obj_daddrs,jm_get,index);
        jclass taskAddr_clazz = env->GetObjectClass(j_taskAddr);

        //获取addrUUID
        jmethodID jm_getAddrUUID = env->GetMethodID(taskAddr_clazz,"getAddrUUID","()Ljava/lang/String;");
        jstring j_addrUUID = (jstring)env->CallObjectMethod(j_taskAddr,jm_getAddrUUID);
        const char* c_addrUUID = env->GetStringUTFChars(j_addrUUID,NULL);
        addrUUID = QString(c_addrUUID);
        env->ReleaseStringUTFChars(j_addrUUID,c_addrUUID);

        //获取isGroup
        jmethodID jm_getIsGroup = env->GetMethodID(taskAddr_clazz,"getIsGroup","()Z");
        bool j_isGroup = false;
        j_isGroup = (bool)env->CallBooleanMethod(j_taskAddr,jm_getIsGroup);
        isGroup = j_isGroup;

        //生成CsRUnstructSendAddr实体， CsRStructSendAddr实体
        DTaskAddr addr;
        addr.setAddrUUID(addrUUID);
        addr.setIsGroup(isGroup);
        addrsList.append(addr);
    }
}

//[3]生成非结构化文件列表实体
void getTaskUnstructFiles(JNIEnv *env, jobject ddEditor_obj, QList<DTaskFile> &uFilesList)
{
    uFilesList.clear();
    jclass ddEditor_clazz = env->GetObjectClass(ddEditor_obj);

    jfieldID fieldID_dsendFiles = env->GetFieldID(ddEditor_clazz,"dunstructSendFiles","Ljava/util/List;");
    jobject obj_dsendFiles = env->GetObjectField(ddEditor_obj,fieldID_dsendFiles);
    jclass clazz_dsendFiles = env->GetObjectClass(obj_dsendFiles);
    jmethodID jm_size = env->GetMethodID(clazz_dsendFiles,"size","()I");
    //files大小
    jint size = env->CallIntMethod(obj_dsendFiles,jm_size);

    QString fileName;fileName.clear();QString srcAbst;srcAbst.clear();
    QString fileDestName;fileDestName.clear();QString saveAbst;saveAbst.clear();
    for(jint index = 0; index <size; index++)
    {
        //TaskFile对象j_taskFile
        fileName.clear();srcAbst.clear();fileDestName.clear();saveAbst.clear();

        jmethodID jm_get = env->GetMethodID(clazz_dsendFiles,"get","(I)Ljava/lang/Object;");
        jobject j_taskFile = env->CallObjectMethod(obj_dsendFiles,jm_get,index);
        jclass taskFile_clazz = env->GetObjectClass(j_taskFile);

        //fileName
        jmethodID jm_getFileName = env->GetMethodID(taskFile_clazz,"getFileName","()Ljava/lang/String;");
        jstring j_fileName = (jstring)env->CallObjectMethod(j_taskFile,jm_getFileName);
        const char* c_fileName = env->GetStringUTFChars(j_fileName,NULL);
        fileName = QString(c_fileName);
        env->ReleaseStringUTFChars(j_fileName,c_fileName);

        //srcAbst
        jmethodID jm_getSrcAbst = env->GetMethodID(taskFile_clazz,"getSrcAbst","()Ljava/lang/String;");
        jstring j_srcAbst = (jstring)env->CallObjectMethod(j_taskFile,jm_getSrcAbst);
        const char* c_srcAbst = env->GetStringUTFChars(j_srcAbst,NULL);
        srcAbst = QString(c_srcAbst);
        env->ReleaseStringUTFChars(j_srcAbst,c_srcAbst);

        //fileDestName
        jmethodID jm_getFileDestName = env->GetMethodID(taskFile_clazz,"getFileDestName","()Ljava/lang/String;");
        jstring j_fileDestName = (jstring)env->CallObjectMethod(j_taskFile,jm_getFileDestName);
        const char* c_fileDestName = env->GetStringUTFChars(j_fileDestName,NULL);
        fileDestName = QString(c_fileDestName);
        env->ReleaseStringUTFChars(j_fileDestName,c_fileDestName);

        //saveAbst
        jmethodID jm_getSaveAbst = env->GetMethodID(taskFile_clazz,"getSaveAbst","()Ljava/lang/String;");
        jstring j_saveAbst = (jstring)env->CallObjectMethod(j_taskFile,jm_getSaveAbst);
        const char* c_saveAbst = env->GetStringUTFChars(j_saveAbst,NULL);
        saveAbst = QString(c_saveAbst);
        env->ReleaseStringUTFChars(j_saveAbst,c_saveAbst);
        output(env,fileName,LogLevel::D);

        //生成非结构化文件列表实体
        DTaskFile taskFile;
        taskFile.setFileName(fileName);
        taskFile.setSrcAbst(srcAbst);
        taskFile.setFileDestName(fileDestName);
        taskFile.setSaveAbst(saveAbst);

        uFilesList.append(taskFile);
    }
}
//[4]生成结构化文件列表实体
void getTaskStructFiles(JNIEnv *env, jobject ddEditor_obj, QList<DTaskFile> &sFilesList)
{
    sFilesList.clear();
    jclass ddEditor_clazz = env->GetObjectClass(ddEditor_obj);

    jfieldID fieldID_dsendFiles = env->GetFieldID(ddEditor_clazz,"dstructSendFiles","Ljava/util/List;");
    jobject obj_dsendFiles = env->GetObjectField(ddEditor_obj,fieldID_dsendFiles);
    jclass clazz_dsendFiles = env->GetObjectClass(obj_dsendFiles);
    jmethodID jm_size = env->GetMethodID(clazz_dsendFiles,"size","()I");
    //files大小
    jint size = env->CallIntMethod(obj_dsendFiles,jm_size);

    QString fileName;fileName.clear();QString srcAbst;srcAbst.clear();
    QString fileDestName;fileDestName.clear();QString saveAbst;saveAbst.clear();
    for(jint index = 0; index <size; index++)
    {
        //TaskFile对象j_taskFile
        fileName.clear();srcAbst.clear();fileDestName.clear();saveAbst.clear();

        jmethodID jm_get = env->GetMethodID(clazz_dsendFiles,"get","(I)Ljava/lang/Object;");
        jobject j_taskFile = env->CallObjectMethod(obj_dsendFiles,jm_get,index);
        jclass taskFile_clazz = env->GetObjectClass(j_taskFile);

        //fileName
        jmethodID jm_getFileName = env->GetMethodID(taskFile_clazz,"getFileName","()Ljava/lang/String;");
        jstring j_fileName = (jstring)env->CallObjectMethod(j_taskFile,jm_getFileName);
        const char* c_fileName = env->GetStringUTFChars(j_fileName,NULL);
        fileName = QString(c_fileName);
        env->ReleaseStringUTFChars(j_fileName,c_fileName);

        //srcAbst
        jmethodID jm_getSrcAbst = env->GetMethodID(taskFile_clazz,"getSrcAbst","()Ljava/lang/String;");
        jstring j_srcAbst = (jstring)env->CallObjectMethod(j_taskFile,jm_getSrcAbst);
        const char* c_srcAbst = env->GetStringUTFChars(j_srcAbst,NULL);
        srcAbst = QString(c_srcAbst);
        env->ReleaseStringUTFChars(j_srcAbst,c_srcAbst);

        //fileDestName
        jmethodID jm_getFileDestName = env->GetMethodID(taskFile_clazz,"getFileDestName","()Ljava/lang/String;");
        jstring j_fileDestName = (jstring)env->CallObjectMethod(j_taskFile,jm_getFileDestName);
        const char* c_fileDestName = env->GetStringUTFChars(j_fileDestName,NULL);
        fileDestName = QString(c_fileDestName);
        env->ReleaseStringUTFChars(j_fileDestName,c_fileDestName);

        //saveAbst
        jmethodID jm_getSaveAbst = env->GetMethodID(taskFile_clazz,"getSaveAbst","()Ljava/lang/String;");
        jstring j_saveAbst = (jstring)env->CallObjectMethod(j_taskFile,jm_getSaveAbst);
        const char* c_saveAbst = env->GetStringUTFChars(j_saveAbst,NULL);
        saveAbst = QString(c_saveAbst);
        env->ReleaseStringUTFChars(j_saveAbst,c_saveAbst);
        output(env,fileName,LogLevel::D);

        //生成结构化文件列表实体
        DTaskFile taskFile;
        taskFile.setFileName(fileName);
        taskFile.setSrcAbst(srcAbst);
        taskFile.setFileDestName(fileDestName);
        taskFile.setSaveAbst(saveAbst);

        sFilesList.append(taskFile);
    }
}

//log output
void output(JNIEnv *env, const QString &msg,const LogLevel &logLevel)
{
    jclass clazz_JNILogUtil = env->FindClass("com/upcloud/ddmi/util/JNILogUtil");
    jmethodID jm_output;
    if(logLevel == LogLevel::D)
    {
        jm_output = env->GetStaticMethodID(clazz_JNILogUtil,"d","(Ljava/lang/String;)V");
    }
    else if(logLevel == LogLevel::I)
    {
        jm_output = env->GetStaticMethodID(clazz_JNILogUtil,"i","(Ljava/lang/String;)V");
    }
    else if(logLevel == LogLevel::E)
    {
        jm_output = env->GetStaticMethodID(clazz_JNILogUtil,"e","(Ljava/lang/String;)V");
    }
    else if(logLevel == LogLevel::F)
    {
        jm_output = env->GetStaticMethodID(clazz_JNILogUtil,"f","(Ljava/lang/String;)V");
    }
    jstring str = env->NewStringUTF(qPrintable(msg));
    env->CallStaticVoidMethod(clazz_JNILogUtil,jm_output,str);
}








