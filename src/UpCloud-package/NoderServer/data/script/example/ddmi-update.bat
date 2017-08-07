@echo off
rem ----------------------------------------------------------------------
rem 
rem 	UpCloud DDMI Libraies Copy Tool
rem
rem	Copyright (c) UpCloud C/C++ development team.
rem	All rights 2015 reserved.
rem
rem 
rem
rem ----------------------------------------------------------------------
cd ..
cd lib
set "libpath=%cd%"
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Core\BaseLib\debug\BaseLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Client-RemoteUI\BaseIRemoteLib\debug\BaseIRemoteLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Client-RemoteUI\BusinessIRemote\HthrobsIRemote\debug\HthrobsIRemote.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Core\TimerLib\debug\TimerLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Core\TransMsgLib\debug\TransMsgLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Client-RemoteUI\BusinessIRemote\OperaIRemote\debug\OperaIRemote.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Core\ActionLib\debug\ActionLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Core\DuplexLib\debug\DuplexLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Core\AvroLib\debug\AvroLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Core\NetLib\debug\NetLib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Client-RemoteUI\NetIRemoteUILib\debug\NetIRemoteUILib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Client-RemoteUI\TimerIRemoteUILib\debug\TimerIRemoteUILib.dll %libpath%
xcopy /y E:\build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug\UpCloud-Client-RemoteUI\NIRemoteUI\UpCloudDDMILib\debug\UpCloudDDMILib.dll %libpath%
:end
@pause