package com.soft.socket;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import javax.microedition.io.Connector;
import javax.microedition.io.SocketConnection;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class SocketClientMIDlet extends MIDlet {

	public SocketClientMIDlet() {
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
			// 1. 建立通信的链路
			String url = "socket://127.0.0.1:9999";
			SocketConnection socketConn = (SocketConnection) Connector.open(url);
		
			// 3.0 打开输入、输出流，与服务器端通信
			DataInputStream dis = socketConn.openDataInputStream();
			DataOutputStream dos = socketConn.openDataOutputStream();
			
			// 3.2 接受数据
			String serverData = dis.readUTF();
			System.out.println("readed form server: " + serverData);
			
			// 3.3 发送数据
			dos.writeUTF("I am client!!!!");
			
			// 3.1 关闭输入、输出流
			dos.close();
			dis.close();
			
			// 2. 关闭连接
			socketConn.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
