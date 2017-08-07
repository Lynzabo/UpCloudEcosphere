package com.upcloud.ddmi.test;

import java.io.IOException;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import com.upcloud.ddmi.UpCloudDDMI;
import com.upcloud.ddmi.core.DDEditor;
import com.upcloud.ddmi.core.dto.Task;
import com.upcloud.ddmi.core.dto.TaskAddr;
import com.upcloud.ddmi.core.dto.TaskFile;
import com.upcloud.ddmi.core.exception.DDMIEditException;
import com.upcloud.ddmi.core.exception.DDMIMetaIllegalException;
import com.upcloud.ddmi.listener.DDMIListener;
import com.upcloud.ddmi.util.JNILogUtil;

public class Test {

	public static void main(String[] args) {
		/*
		 * MathUtil mathUtil = new MathUtil(); mathUtil.output();
		 * System.out.println(111);
		 */
		Test test = new Test();
		try {
			test.loadLibrary("E:/UpCloudEcosphere/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/");
		} catch (IOException e) {
			e.printStackTrace();
		}
		// test.testDDMISend();
		// test.testDDMIDelete();
		test.startupDDMI();
	}

	/**
	 * 开启数据分发服务
	 */
	public void startupDDMI() {
		UpCloudDDMI
				.getInstance()
				.startup(
						"E:/UpCloudEcosphere/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/");
	}

	/**
	 * 销毁数据分发服务
	 */
	public void destoryDDMI() {
		UpCloudDDMI.getInstance().destory();
	}

	public void testDDMIDelete() {
		final String[] uuids = new String[] { "unstruct_UUID", "struct_UUID" };
		new Thread(new Runnable() {
			@Override
			public void run() {
				DDEditor editor = UpCloudDDMI.getInstance().createDDEditor();
				// 业务
				try {
					editor.delete(uuids);
					// Web业务代码
					editor.commit();
				} catch (DDMIMetaIllegalException e) {
				} catch (DDMIEditException e) {
					editor.rollback();
				}
			}
		}).start();
	}

	/**
	 * 使用数据分发服务
	 */
	public void testDDMISend() {
		// 下发任务信息
		final Task task = new Task();
		task.setTaskName("task000001").setDescription("task000001的描述信息")
				.setStrategy((short) 0x1);
		// 待下发节点服务器列表信息
		final List<TaskAddr> addrs = new ArrayList<TaskAddr>();
		TaskAddr addr = new TaskAddr();
		addr.setAddrUUID("1111111");
		addr.setIsGroup(false);
		TaskAddr addr2 = new TaskAddr();
		addr2.setAddrUUID("22ff22");
		addr2.setIsGroup(true);
		addrs.add(addr);
		addrs.add(addr2);
		final List<TaskFile> sendFiles = new ArrayList<TaskFile>();
		TaskFile sendFile = new TaskFile();
		sendFile.setFileName("111.txt").setSrcAbst("d:/111.txt")
				.setFileDestName("111_new.txt").setSaveAbst("/opt");
		sendFiles.add(sendFile);
		TaskFile sendFile2 = new TaskFile();
		sendFile2.setFileName("222.txt").setSrcAbst("d:/222.txt")
				.setFileDestName("222_new.txt").setSaveAbst("/usr/local");
		sendFiles.add(sendFile2);

		new Thread(new Runnable() {
			@Override
			public void run() {
				DDEditor editor = UpCloudDDMI.getInstance().createDDEditor();
				// 可以只setSendFiles,代表下发给所有节点服务器，并且任务信息由数据分发系统生成
				editor.setSendTask(task).setSendAddrs(addrs)
						.setUnstructSendFiles(sendFiles);
				String[] uuids = null;// uuids为返回的非结构化任务UUID和结构化任务UUID
				// 业务
				try {
					uuids = editor.send();
					// Web业务代码
					editor.commit();
				} catch (DDMIMetaIllegalException e) {
					return;
				} catch (DDMIEditException e) {
					editor.rollback();
					return;
				}
			}
		}).start();

	}

	private void loadLibrary(String rPath) throws IOException {
		try {
			// 先配置Qt的安装目录到环境变量Path中
			// D:/Program~Softwares~Files/rubyinstaller_2_2_3_x64/Ruby22-x64/bin;D:/Program~Softwares~Files/Python_3_5_x64/Scripts/;D:/Program~Softwares~Files/Python_3_5_x64/;F:/Java's~Namespace/workspaces/Designs
			// &
			// Models/build-ttewewew1-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/debug;D:/Program~Softwares~Files/Microsoft
			// Visual Studio
			// 12.0/VC/bin/amd64;D:/Program~Softwares~Files/Microsoft
			// SDKs/Bin/x64;C:/Program Files
			// (x86)/Java/jdk1.6.0_43/bin;D:/Program~Softwares~Files/Android/android-sdk-windows/platform-tools;D:/Program~Softwares~Files/Android/android-sdk-windows/tools;C:/Qt/Qt5.4.2-windows-x86-msvc2013_64/5.4/msvc2013_64/bin;C:/Qt/Qt5.4.2-windows-x86-msvc2013_64/5.4/msvc2013_64/bin

			/*
			 * 加载方式1 System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/BaseLib/debug/BaseLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/BaseIRemoteLib/debug/BaseIRemoteLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/BusinessIRemote/HthrobsIRemote/debug/HthrobsIRemote.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/TimerLib/debug/TimerLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/TransMsgLib/debug/TransMsgLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/BusinessIRemote/OperaIRemote/debug/OperaIRemote.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/ActionLib/debug/ActionLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/DuplexLib/debug/DuplexLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/AvroLib/debug/AvroLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/NetLib/debug/NetLib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/NetIRemoteUILib/debug/NetIRemoteUILib.dll"
			 * ); System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/TimerIRemoteUILib/debug/TimerIRemoteUILib.dll"
			 * );
			 * 
			 * System.load(
			 * "E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/NIRemoteUI/UpCloudDDMILib/debug/UpCloudDDMILib.dll"
			 * );
			 */
			// 加载方式2
			DDMIListener.addDir(rPath);
			System.loadLibrary("UpCloudDDMILib");
		} catch (UnsatisfiedLinkError e) {
			e.printStackTrace();
		}
	}

	/**
	 * 添加库 解决直接调用System.setProperty("java.library.path","d:/");加载库文件失败解决办法
	 * 
	 * @param s
	 * @throws IOException
	 */
	public static void addDir(String s) throws IOException {
		try {
			Field field = ClassLoader.class.getDeclaredField("usr_paths");
			field.setAccessible(true);
			String[] paths = (String[]) field.get(null);
			for (int i = 0; i < paths.length; i++) {
				if (s.equals(paths[i])) {
					return;
				}
			}
			String[] tmp = new String[paths.length + 1];
			System.arraycopy(paths, 0, tmp, 0, paths.length);
			tmp[paths.length] = s;
			field.set(null, tmp);
		} catch (IllegalAccessException e) {
			throw new IOException(
					"Failed to get permissions to set library path");
		} catch (NoSuchFieldException e) {
			throw new IOException(
					"Failed to get field handle to set library path");
		}
	}
}
