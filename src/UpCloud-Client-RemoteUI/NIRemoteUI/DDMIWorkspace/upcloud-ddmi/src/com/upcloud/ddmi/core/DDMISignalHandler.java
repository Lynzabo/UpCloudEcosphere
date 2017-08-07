/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : DDMISignalHandler.java
 *      Package : com.upcloud.ddmi.core
 *	      Title : DDMISignalHandler
 *         Time : [2015年12月28日 下午8:48:21] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.core;

import sun.misc.Signal;
import sun.misc.SignalHandler;

/**
 * <div style="text-align:left;margin-left:20px"> <b>类信息</b>
 * <ul>
 * <li><b>ClassName</b> - DDMISignalHandler</li>
 * <li><b>Description</b> - TODO（这里用一句话描述这个类的作用）</li>
 * <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul>
 * 
 * @version 1.0
 * @since 2015年12月28日 下午8:48:21
 * @author Lynzabo </div>
 */
public class DDMISignalHandler implements SignalHandler {

	private SignalHandler oldHandler;
	private StopListener stopListener;
	public void signalAction(Signal signal) {
		stopListener.kill(signal.getName());
	}

	public SignalHandler install(String signalName) {
		Signal diagSignal = new Signal(signalName);
		DDMISignalHandler instance = new DDMISignalHandler();
		instance.oldHandler = Signal.handle(diagSignal, instance);
		return instance;
	}

	@Override
	public void handle(Signal signal) {
		System.out.println("Signal handler called for signal " + signal);
		try {

			signalAction(signal);

			// Chain back to previous handler, if one exists
			if (oldHandler != SIG_DFL && oldHandler != SIG_IGN) {
				oldHandler.handle(signal);
			}

		} catch (Exception e) {
			System.out.println("handle|Signal handler" + "failed, reason "
					+ e.getMessage());
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {

		DDMISignalHandler dsh = new DDMISignalHandler();
		// kill命令
		dsh.install("TERM");
		// ctrl+c命令
		dsh.install("INT");

		System.out.println("Signal handling example.");
		try {
			Thread.sleep(20000);
		} catch (InterruptedException e) {
			System.out.println("Interrupted: " + e.getMessage());
		}

	}
	public void setStopListener(StopListener listener){
		this.stopListener = listener;
	}
	public interface StopListener{
		public void kill(String signalName);
	}
}
