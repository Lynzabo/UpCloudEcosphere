/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : DDEditor.java
 *      Package : com.upcloud.ddmi.core
 *	      Title : DDEditor
 *         Time : [2015年12月26日 上午12:10:40] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.core;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.apache.jasper.tagplugins.jstl.core.ForEach;

import com.upcloud.ddmi.UpCloudDDMI;
import com.upcloud.ddmi.core.dto.Task;
import com.upcloud.ddmi.core.dto.TaskAddr;
import com.upcloud.ddmi.core.dto.TaskFile;
import com.upcloud.ddmi.core.exception.DDMIMetaIllegalException;
import com.upcloud.ddmi.util.CollectionUtil;
import com.upcloud.ddmi.util.StringHelper;
import com.upcloud.ddmi.util.UuidUtil;

/**
 * <div style="text-align:left;margin-left:20px"> <b>类信息</b>
 * <ul>
 * <li><b>ClassName</b> - DDEditor</li>
 * <li><b>Description</b> - 数据分发业务操作方法封装库</li>
 * <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul>
 * 
 * @version 1.0
 * @since 2015年12月26日 上午12:10:40
 * @author Lynzabo </div>
 */
public class DDEditor {

	/**
	 * 确认操作
	 */
	public void commit() {

	}

	/**
	 * 取消操作
	 */
	public void rollback() {

	}

	public DDEditor setSendTask(Task task) {
		if (task != null) {
			dtask = task;
		}
		return this;
	}

	/**
	 * 设置节点服务器信息
	 * 
	 * @param addrs
	 * @return addrs默认为null，当addrs为null,代表下发所有节点服务器，当不为null，addrs可能既有组又有节点服务器
	 */
	public DDEditor setSendAddrs(List<TaskAddr> addrs) {
		if (addrs != null) {
			daddrs = addrs;
		}
		return this;
	}

	public DDEditor setUnstructSendFiles(List<TaskFile> sendFiles) {
		if (sendFiles != null) {
			dunstructSendFiles = sendFiles;
		}
		return this;
	}
	public DDEditor setStructSendFiles(List<TaskFile> sendFiles) {
		if (sendFiles != null) {
			dstructSendFiles = sendFiles;
		}
		return this;
	}
	public DDEditor setDeleteFiles(List<String> delFiles) {
		if (delFiles != null) {
			this.delFiles = delFiles;
		}
		return this;
	}
	/**
	 * 下发服务下发
	 * 
	 * @return 数组为2个元素，元素1代表非结构化任务UUID，元素2代表结构化任务UUID
	 */
	public String[] send() throws DDMIMetaIllegalException {
		validateAndInitSend();
		return doSend();
	}

	private native String[] doSend();

	private native String[] doDelete();
	
	private native void doDelete(String[] uuids);

	private native void doCommit();

	private native void doRollback();

	/**
	 * 发送前校验数据合法性并给未初始化元数据赋初始值
	 */
	private void validateAndInitSend() throws DDMIMetaIllegalException {
		// [1]校验非结构化下发文件
		if(dunstructSendFiles == null) {
			throw new DDMIMetaIllegalException("非结构化下发文件列表为空");		
		} else {
			for (TaskFile dsendFile : dunstructSendFiles) 
			{
				if(dsendFile.getFileName().isEmpty())
				{
					throw new DDMIMetaIllegalException("非结构化下发文件列表中有源文件名为空");
				}
				if(dsendFile.getSrcAbst().isEmpty())
				{
					throw new DDMIMetaIllegalException("非结构化下发文件列表中有源文件路径为空");
				}
				if(dsendFile.getFileDestName().isEmpty())
				{
					throw new DDMIMetaIllegalException("非结构化下发文件列表中有目标文件名为空");
				}
				if(dsendFile.getSaveAbst().isEmpty())
				{
					throw new DDMIMetaIllegalException("非结构化下发文件列表中有目标路径为空");
				}					
			}
		}
		// [1]校验非结构化下发文件
		if(dstructSendFiles == null) {
			throw new DDMIMetaIllegalException("结构化下发文件列表为空");		
		} else {
			for (TaskFile dsendFile : dstructSendFiles) 
			{
				if(dsendFile.getFileName().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有源文件名为空");
				}
				if(dsendFile.getSrcAbst().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有源文件路径为空");
				}
				if(dsendFile.getFileDestName().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有目标文件名为空");
				}
				if(dsendFile.getSaveAbst().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有目标路径为空");
				}					
			}
		}

		// [2]校验任务
		if (dtask == null) {
			dtask = new Task();
			String uuid = UuidUtil.getUUID();
			dtask.setTaskName("任务" + uuid).setDescription("暂无")
			.setStrategy((short) 0x1);
		} else {
			//			if (StringHelper.isEmpty(dtask.getTaskName())) {
			//				String uuid = UuidUtil.getUUID();
			//				dtask.setTaskName("任务" + uuid);
			//				if (StringHelper.isEmpty(dtask.getDescription())) {
			//					dtask.setDescription("暂无");
			//				}
			//			} else if (StringHelper.isEmpty(dtask.getDescription())) {
			//				dtask.setDescription("暂无");
			//			} else if (StringHelper.isEmpty(dtask.getDescription())) {
			//				dtask.setDescription("暂无");
			//			}
			if (StringHelper.isEmpty(dtask.getTaskName()))
			{
				String uuid = UuidUtil.getUUID();
				dtask.setTaskName("任务" + uuid);
			}
			if (StringHelper.isEmpty(dtask.getDescription()))
			{
				dtask.setDescription("暂无");
			}			
		}


		// [3]校验下发地址
		if(daddrs != null)
		{
			for (TaskAddr daddr : daddrs) 
			{
				if(daddr.getAddrUUID().isEmpty())
				{
					throw new DDMIMetaIllegalException("下发地址表中有地址UUID为空");
				}
			}
		}
	}

	/**
	 * 下发服务删除
	 * 
	 * @param uuids
	 */
	public void delete(String[] uuids) throws DDMIMetaIllegalException {
		Boolean isNotEmpty = CollectionUtil.isNotEmpty(uuids);
		if (!isNotEmpty)
			throw new DDMIMetaIllegalException("被删除任务为空");
		if (uuids.length != 2)
			throw new DDMIMetaIllegalException("提供参数数量必须为2个");
		doDelete(uuids);
	}
	/**
	 * 下发服务删除
	 * 
	 * @param uuids
	 */
	public String[] delete() throws DDMIMetaIllegalException {
		validateAndInitDelete();
		return doDelete();
	}
	
	/**
	 * 删除前校验数据合法性并给未初始化元数据赋初始值
	 * @throws DDMIMetaIllegalException
	 */
	private void validateAndInitDelete() throws DDMIMetaIllegalException {
		// [1]校验要删除下发文件列表
		if(delFiles == null) {
			throw new DDMIMetaIllegalException("删除文件列表为空");		
		} else {
			for (String delFile : delFiles) 
			{
				if(delFile.isEmpty())
				{
					throw new DDMIMetaIllegalException("删除文件列表中有文件名为空");
				}								
			}
		}
		// [2]校验结构化下发文件
		if(dstructSendFiles == null) {
			throw new DDMIMetaIllegalException("结构化下发文件列表为空");		
		} else {
			for (TaskFile dsendFile : dstructSendFiles) 
			{
				if(dsendFile.getFileName().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有源文件名为空");
				}
				if(dsendFile.getSrcAbst().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有源文件路径为空");
				}
				if(dsendFile.getFileDestName().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有目标文件名为空");
				}
				if(dsendFile.getSaveAbst().isEmpty())
				{
					throw new DDMIMetaIllegalException("结构化下发文件列表中有目标路径为空");
				}					
			}
		}

		// [2]校验任务
		if (dtask == null) {
			dtask = new Task();
			String uuid = UuidUtil.getUUID();
			dtask.setTaskName("任务" + uuid).setDescription("暂无")
			.setStrategy((short) 0x1);
		} else {
			//			if (StringHelper.isEmpty(dtask.getTaskName())) {
			//				String uuid = UuidUtil.getUUID();
			//				dtask.setTaskName("任务" + uuid);
			//				if (StringHelper.isEmpty(dtask.getDescription())) {
			//					dtask.setDescription("暂无");
			//				}
			//			} else if (StringHelper.isEmpty(dtask.getDescription())) {
			//				dtask.setDescription("暂无");
			//			} else if (StringHelper.isEmpty(dtask.getDescription())) {
			//				dtask.setDescription("暂无");
			//			}
			if (StringHelper.isEmpty(dtask.getTaskName()))
			{
				String uuid = UuidUtil.getUUID();
				dtask.setTaskName("任务" + uuid);
			}
			if (StringHelper.isEmpty(dtask.getDescription()))
			{
				dtask.setDescription("暂无");
			}			
		}


		// [3]校验下发地址
		if(daddrs != null)
		{
			for (TaskAddr daddr : daddrs) 
			{
				if(daddr.getAddrUUID().isEmpty())
				{
					throw new DDMIMetaIllegalException("下发地址表中有地址UUID为空");
				}
			}
		}
	}
	private Task dtask;
	private List<TaskAddr> daddrs;
	private List<TaskFile> dunstructSendFiles;
	private List<TaskFile> dstructSendFiles;
	private List<String> delFiles;
}