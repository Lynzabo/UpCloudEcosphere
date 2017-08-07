/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : DDMIEditException.java
 *      Package : com.upcloud.ddmi.core.exception
 *	      Title : DDMIEditException
 *         Time : [2015年12月29日 下午2:47:56] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.core.exception;

/**
 * <div style="text-align:left;margin-left:20px">
 * <b>类信息</b>
 * <ul>
 * 		<li><b>ClassName</b> - DDMIEditException</li>
 *      <li><b>Description</b> - 下发异常</li>
 *      <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul> 
 * @version 1.0
 * @since 2015年12月29日 下午2:47:56
 * @author Lynzabo
 * </div>
 */
public class DDMIEditException extends DDMIException {
	/**
	 * 
	 */
	public DDMIEditException() {
	}

	/**
	 * @param message
	 */
	public DDMIEditException(String message) {
		super(message);
	}
}
