package com.upcloud.web.test;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.BreakIterator;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.upcloud.ddmi.UpCloudDDMI;
import com.upcloud.ddmi.core.DDEditor;
import com.upcloud.ddmi.core.dto.Task;
import com.upcloud.ddmi.core.dto.TaskAddr;
import com.upcloud.ddmi.core.dto.TaskFile;
import com.upcloud.ddmi.core.exception.DDMIEditException;
import com.upcloud.ddmi.core.exception.DDMIMetaIllegalException;

/**
 * 测试下发一组文件Servlet
 */
public class DDMISendTestServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	public DDMISendTestServlet() {
		super();
	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// [1]下发任务信息
		final Task task = new Task();
		task.setTaskName("task000001").setDescription("task000001的描述信息").setStrategy((short) 0x1);

		// [2]待下发节点服务器列表信息
		final List<TaskAddr> addrs = new ArrayList<TaskAddr>();
		TaskAddr addr = new TaskAddr();
		addr.setAddrUUID("1111111");
		addr.setIsGroup(false);
		TaskAddr addr2 = new TaskAddr();
		addr2.setAddrUUID("22ff22");
		addr2.setIsGroup(true);
		addrs.add(addr);
		addrs.add(addr2);
		// [3]非结构化文件文件列表
		final List<TaskFile> unstructsendFiles = new ArrayList<TaskFile>();
		TaskFile sendFile = new TaskFile();
		sendFile.setFileName("111.txt").setSrcAbst("d:/111.txt").setFileDestName("111_new.txt").setSaveAbst("/opt");
		unstructsendFiles.add(sendFile);
		TaskFile sendFile2 = new TaskFile();
		sendFile2.setFileName("222.txt").setSrcAbst("d:/222.txt").setFileDestName("222_new.txt")
				.setSaveAbst("/usr/local");
		unstructsendFiles.add(sendFile2);

		// [4]结构化文件列表
		final List<TaskFile> structsendFiles = new ArrayList<TaskFile>();
		TaskFile ssendFile = new TaskFile();
		sendFile.setFileName("111.xml").setSrcAbst("d:/111.xml").setFileDestName("111_new.xml").setSaveAbst("/opt");
		structsendFiles.add(ssendFile);
		TaskFile ssendFile2 = new TaskFile();
		sendFile2.setFileName("222.xml").setSrcAbst("d:/222.xml").setFileDestName("222_new.xml")
				.setSaveAbst("/usr/local");
		structsendFiles.add(ssendFile2);

		String jsonStr = "";
		DDEditor editor = UpCloudDDMI.getInstance().createDDEditor();
		editor.setSendTask(task) // 可选 定义任务信息
				.setSendAddrs(addrs)// 可选或者赋值null 定义下发节点服务器地址
				.setUnstructSendFiles(unstructsendFiles)// 必填 定义下发文件信息
				.setStructSendFiles(structsendFiles);// 必填 定义待入库文件信息
		String[] uuids = null;// uuids为返回的非结构化任务UUID和结构化任务UUID
		// 业务
		try {
			uuids = editor.send();
			// Web业务代码
			editor.commit();
			jsonStr = "{\"statusCode\":\"200\",\"message\":\"" + uuids[0] + "-" + uuids[1] + "\"}";
		} catch (DDMIMetaIllegalException ex) {
			jsonStr = "{\"statusCode\":\"201\",\"message\":\"" + ex.getMessage() + "\"}";
		} catch (DDMIEditException ex) {//必须catch该异常
			editor.rollback();
			jsonStr = "{\"statusCode\":\"201\",\"message\":\"" + ex.getMessage() + "\"}";
		}
		response.setCharacterEncoding("UTF-8");
		response.setContentType("application/json; charset=utf-8");
		PrintWriter out = null;
		try {
			out = response.getWriter();
			out.write(jsonStr);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (out != null) {
				out.close();
			}
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

}
