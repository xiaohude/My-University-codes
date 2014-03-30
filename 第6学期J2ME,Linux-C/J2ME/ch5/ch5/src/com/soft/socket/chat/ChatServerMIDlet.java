package com.soft.socket.chat;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import javax.microedition.io.Connector;
import javax.microedition.io.ServerSocketConnection;
import javax.microedition.io.SocketConnection;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ChatServerMIDlet extends MIDlet implements CommandListener {

	private Display display;
	private Form form;
	private TextField dataField;
	private Command sendCmd;
	
	// 建立Socket连接、打开输入输出流
	private ServerSocketConnection serverSocketConn;
	private SocketConnection socketConn;
	
	private DataInputStream dis;
	private DataOutputStream dos;
	
	public ChatServerMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("Chat Server");
		dataField = new TextField("Data: ", "", 16, TextField.ANY);
		sendCmd = new Command("Send", Command.SCREEN, 1);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		if (dis != null) {
			try {
				dis.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (dos != null) {
			try {
				dos.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		if (socketConn != null) {
			try {
				socketConn.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		if (serverSocketConn != null) {
			try {
				serverSocketConn.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(form);
		
		form.append(dataField);
		
		form.addCommand(sendCmd);
		form.setCommandListener(this);
		
		new Thread(new SocektThread()).start();
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == sendCmd) {
			// 接收到用户的输入，发送出去
			String data = dataField.getString();
			try {
				dos.writeUTF(data);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	class SocektThread implements Runnable {
		
		public SocektThread() {
			
			try {
				String url = "socket://:9999";
				serverSocketConn = (ServerSocketConnection) Connector.open(url);
			
				socketConn = (SocketConnection) serverSocketConn.acceptAndOpen();
			
				dos = socketConn.openDataOutputStream();
				dis = socketConn.openDataInputStream();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		public void run() {
			while(true) {
				
				// 读入数据
				String clientData = "";
				try {
					clientData = dis.readUTF();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
				form.append("Client: " + clientData + "\n");
				
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
