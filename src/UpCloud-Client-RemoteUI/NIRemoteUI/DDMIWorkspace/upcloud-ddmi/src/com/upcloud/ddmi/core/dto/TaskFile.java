/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : TaskFiles.java
 *      Package : com.upcloud.ddmi.core.dto
 *	      Title : TaskFiles
 *         Time : [2015年12月26日 上午12:19:21] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.core.dto;

/**
 * <div style="text-align:left;margin-left:20px"> <b>类信息</b>
 * <ul>
 * <li><b>ClassName</b> - TaskFile</li>
 * <li><b>Description</b> - 任务下发的文件信息</li>
 * <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul>
 * 
 * @version 1.0
 * @since 2015年12月26日 上午12:19:21
 * @author Lynzabo </div>
 */
public class TaskFile {
	/**
	 * 原文件名
	 */
	private String fileName;
	/**
	 * 源文件路径
	 */
	private String srcAbst;
	/**
	 * 新文件名
	 */
	private String fileDestName;
	/**
	 * 文件保存路径
	 */
	private String saveAbst;

	public String getFileName() {
		return fileName;
	}

	public TaskFile setFileName(String fileName) {
		this.fileName = fileName;
		return this;
	}



	public String getSrcAbst() {
		return srcAbst;
	}

	public TaskFile setSrcAbst(String srcAbst) {
		this.srcAbst = srcAbst;
		return this;
	}

	public String getFileDestName() {
		return fileDestName;
	}

	public TaskFile setFileDestName(String fileDestName) {
		this.fileDestName = fileDestName;
		return this;
	}

	public String getSaveAbst() {
		return saveAbst;
	}

	public TaskFile setSaveAbst(String saveAbst) {
		this.saveAbst = saveAbst;
		return this;
	}

}
