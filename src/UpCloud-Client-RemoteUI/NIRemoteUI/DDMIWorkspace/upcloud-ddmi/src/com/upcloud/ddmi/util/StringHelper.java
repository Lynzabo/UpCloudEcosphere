/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : StringHelper.java
 *      Package : com.upcloud.ddmi.util
 *	      Title : StringHelper
 *         Time : [2015年12月26日 上午2:09:16] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.util;

/**
 * <div style="text-align:left;margin-left:20px"> <b>类信息</b>
 * <ul>
 * <li><b>ClassName</b> - StringHelper</li>
 * <li><b>Description</b> - 字符串常用工具方法</li>
 * <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul>
 * 
 * @version 1.0
 * @since 2015年12月26日 上午2:09:16
 * @author Lynzabo </div>
 */
public class StringHelper {

	/**
	 * 
	 */
	protected StringHelper() {
	}

	public static boolean isNotEmpty(String string) {
		return string != null && string.trim().length() > 0;
	}

	public static boolean isEmpty(String string) {
		return string == null || string.trim().length() == 0;
	}

	public static boolean isEmpty(String... args) {
		for (String str : args) {
			if (isEmpty(str)) {
				return true;
			}
		}
		return false;
	}

	public static boolean isNotEmpty(String... args) {
		return !isEmpty(args);
	}
}
