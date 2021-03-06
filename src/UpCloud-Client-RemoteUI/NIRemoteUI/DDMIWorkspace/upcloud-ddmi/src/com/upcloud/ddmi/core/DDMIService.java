/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : DDMIService.java
 *      Package : com.upcloud.ddmi.core
 *	      Title : DDMIService
 *         Time : [2015年12月28日 下午3:13:39] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.core;

/**
 * <div style="text-align:left;margin-left:20px">
 * <b>类信息</b>
 * <ul>
 * 		<li><b>ClassName</b> - DDMIService</li>
 *      <li><b>Description</b> - DDMI服务</li>
 *      <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul> 
 * @version 1.0
 * @since 2015年12月28日 下午3:13:39
 * @author Lynzabo
 * </div>
 */
public class DDMIService {
	/**
	 * 开启服务
	 */
	public native void startup(String ddmiPath);
	/**
	 * 停止服务
	 */
	public native void destory();
}
