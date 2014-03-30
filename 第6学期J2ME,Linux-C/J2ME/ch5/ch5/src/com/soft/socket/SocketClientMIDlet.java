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
			// 1. ����ͨ�ŵ���·
			String url = "socket://127.0.0.1:9999";
			SocketConnection socketConn = (SocketConnection) Connector.open(url);
		
			// 3.0 �����롢����������������ͨ��
			DataInputStream dis = socketConn.openDataInputStream();
			DataOutputStream dos = socketConn.openDataOutputStream();
			
			// 3.2 ��������
			String serverData = dis.readUTF();
			System.out.println("readed form server: " + serverData);
			
			// 3.3 ��������
			dos.writeUTF("I am client!!!!");
			
			// 3.1 �ر����롢�����
			dos.close();
			dis.close();
			
			// 2. �ر�����
			socketConn.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
