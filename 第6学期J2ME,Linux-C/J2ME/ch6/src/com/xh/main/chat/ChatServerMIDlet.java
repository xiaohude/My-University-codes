package com.xh.main.chat;

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
	private SocketConnection socketConn1;
	private SocketConnection socketConn2;
	
	private DataInputStream dis1;
	private DataOutputStream dos1;
	
	private DataInputStream dis2;
	private DataOutputStream dos2;
	
	public ChatServerMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("Chat Server");
		
		dataField = new TextField("发送给所有客户: ", "", 16, TextField.ANY);
		sendCmd = new Command("发送", Command.SCREEN, 1);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		if (dis1 != null) {
			try {
				dis1.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (dos1 != null) {
			try {
				dos1.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		if (socketConn1 != null) {
			try {
				socketConn1.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (socketConn1 != null) {
			try {
				socketConn2.close();
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
		form.append("客户端的消息记录：\n");
		form.addCommand(sendCmd);
		form.setCommandListener(this);
		
		//new Thread(new SocektThread()).start();
		
		try {
			String url = "socket://:9999";////这里的9999算是自己设置的一个服务器的端口号。
			serverSocketConn = (ServerSocketConnection) Connector.open(url);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		new Thread(new SocektThread1()).start();
		new Thread(new SocektThread2()).start();
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == sendCmd) {
			// 接收到服务器的输入，发送给所有客户
			String data = dataField.getString();
			try {
				dos1.writeUTF("Server："+data);
				dos2.writeUTF("Server："+data);
				dataField.setString("");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	/*class SocektThread implements Runnable {
		
		public SocektThread() {
			
			try {
				String url = "socket://:9999";////这里的9999算是自己设置的一个服务器的端口号。
				serverSocketConn = (ServerSocketConnection) Connector.open(url);
			
				socketConn1 = (SocketConnection) serverSocketConn.acceptAndOpen();			
				dos1 = socketConn1.openDataOutputStream();
				dis1 = socketConn1.openDataInputStream();
				System.out.println("连接1的地址为："+socketConn1.getAddress());///输出和他连接的用户地址；
				System.out.println("当前地址为："+socketConn1.getLocalAddress());///输出和他连接的用户地址；
				
				socketConn2 = (SocketConnection) serverSocketConn.acceptAndOpen();			
				dos2 = socketConn2.openDataOutputStream();
				dis2 = socketConn2.openDataInputStream();
				System.out.println("连接2的地址为："+socketConn2.getAddress());///输出和他连接的用户地址；
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
					clientData = dis1.readUTF();
					//if(clientData=="")break;////防止另一个终端关闭后dis无法阻塞，导致一直死循环。
					dos2.writeUTF(clientData);				
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				if(clientData=="")break;////防止另一个终端关闭后dis无法阻塞，导致一直死循环。
				form.append("Client: " + clientData + "\n");
				
				try {
					Thread.currentThread().sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}*/
	
	class SocektThread1 implements Runnable {
		public SocektThread1() {
			try {
				socketConn1 = (SocketConnection) serverSocketConn.acceptAndOpen();
				dos1 = socketConn1.openDataOutputStream();
				dis1 = socketConn1.openDataInputStream();
				System.out.println("连接1的地址为："+socketConn1.getAddress());///输出和他连接的用户地址；
				System.out.println("当前地址为："+socketConn1.getLocalAddress());///输出和他连接的用户地址；
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}				
		}

		public void run() {
			String clientData = "";
			while(true)	
			{
				try {
					clientData = dis1.readUTF();			
					dos2.writeUTF("Client1："+clientData);		
					if(clientData=="")break;////防止另一个终端关闭后dis无法阻塞，导致一直死循环。
					form.append("Client1: " + clientData + "\n");		
				} catch (IOException e) {
					e.printStackTrace();
				}		
			}
		}
	}
	class SocektThread2 implements Runnable {
		public SocektThread2() {
			try {
				socketConn2 = (SocketConnection) serverSocketConn.acceptAndOpen();
				dos2 = socketConn2.openDataOutputStream();
				dis2 = socketConn2.openDataInputStream();
				System.out.println("连接2的地址为："+socketConn2.getAddress());///输出和他连接的用户地址；
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}					
		}
		public void run() {
			String clientData = "";
			while(true)
			{
				try {
					clientData = dis2.readUTF();
					dos1.writeUTF("Client2："+clientData);
					if(clientData=="")break;////防止另一个终端关闭后dis无法阻塞，导致一直死循环。
					form.append("Client2: " + clientData + "\n");
				} catch (IOException e) {
					if(e.equals(dis2))
					{
						System.out.println("dis2出现异常！");
						break;
					}
					e.printStackTrace();
				}		
			}
		
		}
	}
}
