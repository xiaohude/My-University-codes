package com.soft.socket.chat;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import javax.microedition.io.Connector;
import javax.microedition.io.SocketConnection;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ChatClientMIDlet extends MIDlet implements CommandListener {
	private Display display;
	private Form form;
	private TextField dataField;
	private Command sendCmd;
	
	// ����Socket���ӡ������������
	private SocketConnection socketConn;
	
	private DataInputStream dis;
	private DataOutputStream dos;
	
	public ChatClientMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("Chat Client");
		dataField = new TextField("Data: ", "", 16, TextField.ANY);
		sendCmd = new Command("Send", Command.SCREEN, 1);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(form);
		
		form.append(dataField);
		
		form.addCommand(sendCmd);
		form.setCommandListener(this);
		
		new Thread(new ClientThread()).start();

	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == sendCmd) {
			// ���յ��û������룬���ͳ�ȥ
			String data = dataField.getString();
			try {
				dos.writeUTF(data);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	class ClientThread implements Runnable {
		public ClientThread() {
			
			try {
				String url = "socket://127.0.0.1:9999";
				socketConn = (SocketConnection) Connector.open(url);
			
				dos = socketConn.openDataOutputStream();
				dis = socketConn.openDataInputStream();
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		public void run() {
while(true) {
				
				// ��������
				String serverData = "";
				try {
					serverData = dis.readUTF();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
				form.append("Server: " + serverData + "\n");
				
				try {
					Thread.currentThread().sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

}
