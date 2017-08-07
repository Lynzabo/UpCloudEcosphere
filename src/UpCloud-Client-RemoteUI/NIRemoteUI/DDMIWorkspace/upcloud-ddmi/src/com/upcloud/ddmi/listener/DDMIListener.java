package com.upcloud.ddmi.listener;

import java.io.IOException;
import java.lang.reflect.Field;
import java.util.Timer;
import java.util.TimerTask;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

import org.apache.log4j.Logger;

import com.upcloud.ddmi.UpCloudDDMI;
import com.upcloud.ddmi.core.DDMISignalHandler;
import com.upcloud.ddmi.core.DDMISignalHandler.StopListener;

public class DDMIListener implements ServletContextListener,StopListener {
	private static final Logger logger = Logger.getLogger(DDMIListener.class);
	/*
	 * @Override public void contextInitialized(ServletContextEvent arg0) {
	 * logger.debug("上云科技数据分发服务准备启动..."); new Thread(new Runnable() {
	 * 
	 * @Override public void run() { UpCloudDDMI .getInstance() .startup(
	 * "E:/UpCloudEcosphere/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/"
	 * ); } }).start(); }
	 * 
	 * @Override public void contextDestroyed(ServletContextEvent arg0) {
	 * logger.debug("上云科技数据分发服务准备销毁..."); UpCloudDDMI.getInstance().destory();
	 * logger.debug("上云科技数据分发服务销毁完毕"); }
	 */
	Timer timer;

	public void contextInitialized(ServletContextEvent e) {
		logger.debug("上云科技数据分发服务客户端插件启动...");
		logger.debug("1.准备加载数据分发服务客户端插件库文件");
		final String rPath = e.getServletContext().getRealPath("/").replaceAll("\\\\", "/")+"upcloud-ddmi/";
		String rLib = rPath + "lib/";
		try {
			loadLibrary(rLib);
			logger.debug("加载成功");
		} catch (IOException e1) {
			e1.printStackTrace();
			logger.error(e1.getMessage());
			return;
		}
		logger.debug("2.准备绑定中间件信号");
		//铺货JVM退出命令
		DDMISignalHandler dsh = new DDMISignalHandler();
		// kill命令
		dsh.install("TERM");
		// ctrl+c命令
		dsh.install("INT");
		dsh.setStopListener(this);
		logger.debug("绑定成功");
		logger.debug("3.启动数据分发客户端插件");
		//启动服务
		this.timer = new Timer();
		this.timer.schedule(new TimerTask() {
			public void run() {
				try {
					UpCloudDDMI
							.getInstance()
							.startup(rPath);
				} catch (Exception e) {
					DDMIListener.logger.error("", e);
				}

			}
		}, 0L, (long) (5 * 60) * 1000L);

	}

	public void contextDestroyed(ServletContextEvent e) {
		logger.debug("上云科技数据分发服务客户端插件准备销毁...");
		UpCloudDDMI.getInstance().destory();
		logger.debug("上云科技数据分发服务客户端插件销毁完毕");
	}

	@Override
	public void kill(String signalName) {
		contextDestroyed(null);
	}
	private void loadLibrary(String rPath) throws IOException{
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
			加载方式1
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/BaseLib/debug/BaseLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/BaseIRemoteLib/debug/BaseIRemoteLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/BusinessIRemote/HthrobsIRemote/debug/HthrobsIRemote.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/TimerLib/debug/TimerLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/TransMsgLib/debug/TransMsgLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/BusinessIRemote/OperaIRemote/debug/OperaIRemote.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/ActionLib/debug/ActionLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/DuplexLib/debug/DuplexLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/AvroLib/debug/AvroLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/NetLib/debug/NetLib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/NetIRemoteUILib/debug/NetIRemoteUILib.dll");
			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/TimerIRemoteUILib/debug/TimerIRemoteUILib.dll");

			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/NIRemoteUI/UpCloudDDMILib/debug/UpCloudDDMILib.dll");*/
			//加载方式2
			logger.debug("库文件路径:"+rPath);
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/BaseLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/BaseIRemoteLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/HthrobsIRemote.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/TimerLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/TransMsgLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/OperaIRemote.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/ActionLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/DuplexLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/AvroLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/NetLib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/NetIRemoteUILib.dll");
//			System.load("E:/new/UpCloud-Client-RemoteUI/NIRemoteUI/DDMIWorkspace/upcloud-ddmi/WebContent/upcloud-ddmi/lib/TimerIRemoteUILib.dll");
//
//			System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/NIRemoteUI/UpCloudDDMILib/debug/UpCloudDDMILib.dll");
			DDMIListener.addDir(rPath);
			System.loadLibrary("UpCloudDDMILib");
		} catch (UnsatisfiedLinkError e) {
			e.printStackTrace();
		}
	}
	/**
	 * 添加库
	 * 解决直接调用System.setProperty("java.library.path","d:/");加载库文件失败解决办法
	 * @param s
	 * @throws IOException
	 */
	public static void addDir(String s) throws IOException {
		try {
			Field field = ClassLoader.class.getDeclaredField("usr_paths");
			field.setAccessible(true);
			String[] paths = (String[])field.get(null);
			for (int i = 0; i < paths.length; i++) {
				if (s.equals(paths[i])) {
					return;
				}
			}
			String[] tmp = new String[paths.length+1];
			System.arraycopy(paths,0,tmp,0,paths.length);
			tmp[paths.length] = s;
			field.set(null,tmp);
		} catch (IllegalAccessException e) {
			throw new IOException("Failed to get permissions to set library path");
		} catch (NoSuchFieldException e) {
			throw new IOException("Failed to get field handle to set library path");
		}
	}
}
