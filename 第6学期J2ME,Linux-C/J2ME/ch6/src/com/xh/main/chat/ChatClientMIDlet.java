package com.xh.main.chat;

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
	
	// 建立Socket连接、打开输入输出流
	private SocketConnection socketConn;
	
	private DataInputStream dis;
	private DataOutputStream dos;
	
	public ChatClientMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("Chat Client1");
		dataField = new TextField("信息: ", "", 16, TextField.ANY);
		sendCmd = new Command("发送", Command.SCREEN, 1);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub
		try {
			dos.close();
			dis.close();
			socketConn.close();
					
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
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
		
		new Thread(new ClientThread()).start();

	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == sendCmd) {
			// 接收到用户的输入，发送出去
			String data = dataField.getString();
			try {
				dos.writeUTF(data);
				dataField.setString("");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	class ClientThread implements Runnable {
		public ClientThread() {
			
			try {
				String url = "socket://127.0.0.1:9999";//设置自己的地址为127.0.0.1向端口为9999的服务器发送
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
				
				// 读入数据
				String serverData = "";
				try {
					serverData = dis.readUTF();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				if(serverData=="")break;
				form.append(serverData + "\n");
				
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
