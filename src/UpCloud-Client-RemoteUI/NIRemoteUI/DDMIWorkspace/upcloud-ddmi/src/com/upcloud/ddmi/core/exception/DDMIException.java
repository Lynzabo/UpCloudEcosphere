/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : DDMIException.java
 *      Package : com.upcloud.ddmi.core.exception
 *	      Title : DDMIException
 *         Time : [2015年12月26日 上午1:03:40] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.core.exception;

/**
 * <div style="text-align:left;margin-left:20px">
 * <b>类信息</b>
 * <ul>
 * 		<li><b>ClassName</b> - DDMIException</li>
 *      <li><b>Description</b> - TODO（这里用一句话描述这个类的作用）</li>
 *      <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul> 
 * @version 1.0
 * @since 2015年12月26日 上午1:03:40
 * @author Lynzabo
 * </div>
 */
public class DDMIException extends RuntimeException {

	public DDMIException() {
		super();
	}

	public DDMIException(String message, Throwable cause) {
		super(message, cause);
	}

	public DDMIException(String message) {
		super(message);
	}

	public DDMIException(Throwable cause) {
		super(cause);
	}
	
}
