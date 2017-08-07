/**
 * Copyright (c) UpCloud C/C++ development team.
 * All rights 2015 reserved.
 *
 *      Project : upcloud-ddmi
 *     FileName : CollectionUtil.java
 *      Package : com.upcloud.ddmi.util
 *	      Title : CollectionUtil
 *         Time : [2015年12月26日 上午1:08:58] 
 *       Author : Lynzabo
 *       Verion : 1.0
 */
package com.upcloud.ddmi.util;

import java.lang.reflect.Array;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

/**
 * <div style="text-align:left;margin-left:20px"> <b>类信息</b>
 * <ul>
 * <li><b>ClassName</b> - CollectionUtil</li>
 * <li><b>Description</b> - TODO（这里用一句话描述这个类的作用）</li>
 * <li><b>Notice</b> - 所有的常量必须有注释,并且应该用"域注释"</li>
 * </ul>
 * 
 * @version 1.0
 * @since 2015年12月26日 上午1:08:58
 * @author Lynzabo </div>
 */
public class CollectionUtil {
	public static boolean isNotEmpty(Object target) {
		if(target instanceof Collection<?>){
			Collection<?> contas = (Collection<?>)target;
			return contas!=null&&contas.size()>0;
		}else if(target instanceof String[]){
			String[] contas = (String[])target;
			return contas!=null&&contas.length>0;
		}else{
			return target!=null;
		}
	}
}
