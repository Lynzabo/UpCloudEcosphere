import java.io.IOException;
public class Test {
	public native void output();
	public static void main(String[] args) throws IOException {
		System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Core/BaseLib/debug/BaseLib.dll");
		System.load("E:/build-UpCloudEcosphere-Desktop_Qt_5_4_2_MSVC2013_64bit-Debug/UpCloud-Client-RemoteUI/NIRemoteUI/dddddd/debug/dddddd.dll");
		Test test= new Test();
		test.output();
	}

}
