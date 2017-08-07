<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script type="text/javascript"
	src="<%=basePath%>common/js/jquery-1.7.2.min.js"></script>
<title>数据分发服务Web调用测试</title>
<style>
input[type=button] {
	font-size: 20px;
}
</style>
<script type="text/javascript">
$(document).ready(function () {
	$("#sendBtn").click(function(){
		asyncExec("<%=basePath%>DDMISendTestServlet");
	});
	$("#delBtn").click(function(){
		asyncExec("<%=basePath%>DDMIDeleteTestServlet");
	});
});
			function asyncExec(toUrl){
				$.ajax({
					url: toUrl,
				    type: 'post',
				    dataType: 'json',
				    // timeout: 30000,
				    error: function(){
				    	alert('系统繁忙,请稍候再试!');
				    	restoreInfo();
				    },
				    success: function(json){	    
				    	var result = json.statusCode;
						var message = json.message;
						if(result=="200"){
							alert("操作任务成功:"+message);
						}else{
							alert("操作任务失败:"+message);
						}
					}
			    });
			}
</script>
</head>
<body style="margin-top: 300px; text-align: center">
	<input type="button" value="测试下发" id="sendBtn" />
	<br />
	<br />
	<input type="button" value="测试删除" id="delBtn" />
</body>
</html>