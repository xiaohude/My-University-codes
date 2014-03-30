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
			// 1. �����������˵ļ���
			String url = "socket://:9999";
			ServerSocketConnection serverConn = (ServerSocketConnection) Connector.open(url);
		
			// 3. ����ͨ����·
			System.out.println("before!!!!");
			SocketConnection socketConn = (SocketConnection) serverConn.acceptAndOpen();
			System.out.println("after!!!!");
			
			// 4.0 ��ͻ���ͨ�ţ���Ҫ�������������
			DataOutputStream dos = socketConn.openDataOutputStream();
			DataInputStream dis = socketConn.openDataInputStream();
			
			// 4.2 ��������
			dos.writeUTF("Connected Succ!");
			
			// 4.3 ��������
			String clientData = dis.readUTF();
			System.out.println("readed form client: " + clientData);
			
			// 4.1 �ر����롢�����
			dos.close();
			dis.close();
			
			// 2. �ر�����
			socketConn.close();
			serverConn.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
