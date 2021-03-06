/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : UuidUtil.java
 *      Package : com.upcloud.ddmi.util
 *	      Title : UuidUtil
 *         Time : [2015年12月26日 上午2:02:36] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.util;

import org.apache.commons.id.IdentifierGeneratorFactory;
import org.apache.commons.id.StringIdentifierGenerator;

/**
 * <div style="text-align:left;margin-left:20px">
 * <b>类信息</b>
 * <ul>
 * 		<li><b>ClassName</b> - UuidUtil</li>
 *      <li><b>Description</b> - 生成随机数</li>
 *      <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul> 
 * @version 1.0
 * @since 2015年12月26日 上午2:02:36
 * @author Lynzabo
 * </div>
 */
public class UuidUtil {

	/**
	 * 
	 */
	protected UuidUtil() {
	}
	protected static IdentifierGeneratorFactory factory = IdentifierGeneratorFactory.newInstance();
	public static StringIdentifierGenerator gSession = factory.sessionIdGenerator();
	public static String getUUID() {
		return gSession.nextStringIdentifier() + gSession.nextStringIdentifier();
	}
}
