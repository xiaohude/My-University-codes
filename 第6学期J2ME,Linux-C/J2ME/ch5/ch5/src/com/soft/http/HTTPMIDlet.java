package com.soft.http;

import java.io.IOException;
import java.io.InputStream;

import javax.microedition.io.Connector;
import javax.microedition.io.HttpConnection;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class HTTPMIDlet extends MIDlet {

	public HTTPMIDlet() {
		// TODO Auto-generated constructor stub
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		
		try {
			// 1. ����HTTP����
			String url = "http://127.0.0.1:8080/j2me/get.jsp?name=zhangsan&passwd=1234";
			HttpConnection httpConn = (HttpConnection) Connector.open(url);
			
			// 3. �������󷽷�
			httpConn.setRequestMethod(HttpConnection.GET);
			
			// 4. ��ȡ���
			
			
			InputStream is = httpConn.openInputStream();
			
			int len = (int) httpConn.getLength();
			
			byte[] buffer = new byte[len];
			
			is.read(buffer);
			System.out.println("reade form tomcat: " + new String(buffer));
			
			
			// 2. �ر�����
			httpConn.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
