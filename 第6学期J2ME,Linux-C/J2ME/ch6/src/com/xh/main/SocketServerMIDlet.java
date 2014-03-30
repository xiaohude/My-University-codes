package com.xh.main;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import javax.microedition.io.Connector;
import javax.microedition.io.ServerSocketConnection;
import javax.microedition.io.SocketConnection;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class SocketServerMIDlet extends MIDlet {

	public SocketServerMIDlet() {
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
			// 1. 建立服务器端的监听
			String url = "socket://:9999";
			ServerSocketConnection serverConn = (ServerSocketConnection) Connector.open(url);
		
			// 3. 建立通信链路
			System.out.println("before!!!!");
			SocketConnection socketConn = (SocketConnection) serverConn.acceptAndOpen();
			System.out.println("after!!!!");
			
			// 4.0 与客户端通信，需要打开输出、输入流
			DataOutputStream dos = socketConn.openDataOutputStream();
			DataInputStream dis = socketConn.openDataInputStream();
			
			// 4.2 发送数据
			dos.writeUTF("Connected Succ!");
			
			// 4.3 接受数据
			String clientData = dis.readUTF();
			System.out.println("readed form client: " + clientData);
			
			// 4.1 关闭输入、输出流
			dos.close();
			dis.close();
			
			// 2. 关闭连接
			socketConn.close();
			serverConn.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
