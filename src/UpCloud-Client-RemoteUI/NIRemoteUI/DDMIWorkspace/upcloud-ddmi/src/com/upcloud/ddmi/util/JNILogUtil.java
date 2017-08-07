/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : LogUtil.java
 *      Package : com.upcloud.ddmi.util
 *	      Title : LogUtil
 *         Time : [2015年12月28日 下午1:26:27] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.util;

import org.apache.log4j.Logger;

import com.upcloud.ddmi.listener.DDMIListener;

/**
 * <div style="text-align:left;margin-left:20px"> <b>类信息</b>
 * <ul>
 * <li><b>ClassName</b> - LogUtil</li>
 * <li><b>Description</b> - JNI异常输出</li>
 * <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul>
 * 
 * @version 1.0
 * @since 2015年12月28日 下午1:26:27
 * @author Lynzabo </div>
 */
public class JNILogUtil {
	private static final Logger logger = Logger.getLogger(JNILogUtil.class);

	public static synchronized void d(String msg) {
		logger.debug(msg);
	}

	public static synchronized void i(String msg) {
		logger.info(msg);
	}

	public static synchronized void e(String msg) {
		logger.error(msg);
	}

	public static synchronized void f(String msg) {
		logger.fatal(msg);
	}
}
