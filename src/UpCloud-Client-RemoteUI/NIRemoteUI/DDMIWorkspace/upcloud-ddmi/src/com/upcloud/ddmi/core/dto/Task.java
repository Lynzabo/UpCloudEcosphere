/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : Task.java
 *      Package : com.upcloud.ddmi.core.dto
 *	      Title : Task
 *         Time : [2015年12月26日 上午12:17:36] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.core.dto;

import com.upcloud.ddmi.UpCloudDDMI;

/**
 * <div style="text-align:left;margin-left:20px"> <b>类信息</b>
 * <ul>
 * <li><b>ClassName</b> - Task</li>
 * <li><b>Description</b> - TODO（这里用一句话描述这个类的作用）</li>
 * <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul>
 * 
 * @version 1.0
 * @since 2015年12月26日 上午12:17:36
 * @author Lynzabo </div>
 */
public class Task {
	/**
	 * 任务名称
	 */
	private String taskName;
	/**
	 * 任务描述
	 */
	private String description;
	/**
	 * 下发策略
	 */
	private short strategy;

	public String getTaskName() {
		return taskName;
	}

	public Task setTaskName(String taskName) {
		this.taskName = taskName;
		return this;
	}

	public String getDescription() {
		return description;
	}

	public Task setDescription(String description) {
		this.description = description;
		return this;
	}

	public short getStrategy() {
		return strategy;
	}

	public Task setStrategy(short strategy) {
		this.strategy = strategy;
		return this;
	}

}
