/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#include "delonegroupthread.h"
#include "base.h"
DelOneGroupThread::DelOneGroupThread()
{
    m_files.clear();
    m_dirs.clear();
    m_posNames.clear();

}

DelOneGroupThread::~DelOneGroupThread()
{
    m_posNames.clear();
    m_files.clear();
    m_dirs.clear();
}

void DelOneGroupThread::init(const QList<QString> &posNames)
{
    m_posNames = posNames;
}

void DelOneGroupThread::run()
{
  if(m_posNames.size() <= 0)
  {
      emit evt_delEnd();
      return;
  }
  else
  {
      //预处理---剔除空的 不是文件也不是目录的
      for(int i=0; i<m_posNames.size(); i++)
      {
          QFileInfo fileInfo(m_posNames.at(i));
          //判断文件/目录是否存在
          bool isExist = fileInfo.exists();
          if(isExist == false)
          {
              emit evt_delOneError(m_posNames.at(i), "obj is not exist");
              qDebug() << m_posNames.at(i) << "  obj is not exist" << QThread::currentThreadId();
          }
          else
          {
              if(fileInfo.isFile() == true)
              {
                  m_files.append(m_posNames.at(i));
              }
              else if(fileInfo.isDir() == true)
              {
                  m_dirs.append(m_posNames.at(i));
              }
              else
              {
                  emit evt_delOneError(m_posNames.at(i), "obj type is not file or dir");
                  qDebug() << m_posNames.at(i) << "  obj type is not file or dir"<< QThread::currentThreadId();
              }
          }
      }
      //对于文件的删除
      for(int i=0; i<m_files.size(); i++)
      {
          //删除文件
          bool isRm = QFile::remove(m_files.at(i));
          if(isRm == true)
          {
              emit evt_delOneEnd(m_files.at(i));
              qDebug() << m_files.at(i) << "  ok"<< QThread::currentThreadId();
          }
          else
          {
              emit evt_delOneError(m_files.at(i), "del file error");
              qDebug() << m_files.at(i) << "  del file error"<< QThread::currentThreadId();
          }
      }
      //对于目录的删除
      for(int i=0; i<m_dirs.size(); i++)
      {
          //删除目录
          bool isRm = DirUtil::DeleteDirectory(m_dirs.at(i));
          if(isRm == true)
          {
              emit evt_delOneEnd(m_dirs.at(i));
              qDebug() << m_dirs.at(i) << " ok"<< QThread::currentThreadId();
          }
          else
          {
              emit evt_delOneError(m_dirs.at(i), "del dir error");
              qDebug() << m_dirs.at(i) << "  del dir error"<< QThread::currentThreadId();
          }
      }
      emit evt_delEnd();
      return;
  }
}

