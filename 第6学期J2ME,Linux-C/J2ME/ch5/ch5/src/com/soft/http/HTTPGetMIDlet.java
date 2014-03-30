package com.soft.http;

import java.io.IOException;
import java.io.InputStream;

import javax.microedition.io.Connector;
import javax.microedition.io.HttpConnection;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class HTTPGetMIDlet extends MIDlet implements CommandListener {
	private Display display;
	private Form form;
	private TextField nameField;
	private TextField passwdField;
	private Command loginCmd;
	
	public HTTPGetMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("HTTP Form");
		nameField = new TextField("Name: ", "", 16, TextField.ANY);
		passwdField = new TextField("Passwd: " , "", 16, TextField.ANY);
		loginCmd = new Command("Login", Command.SCREEN, 1);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(form);
		
		form.append(nameField);
		form.append(passwdField);
		
		form.addCommand(loginCmd);
		form.setCommandListener(this);
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == loginCmd) {
			new Thread(new HTTPThread()).start();

		}// end of if
			
	}
		
	class HTTPThread implements Runnable {
		public void run() {
			// ��ȡ����������ݣ���������Tomcat
			String name = nameField.getString();
			String passwd = passwdField.getString();
			// HTTP
			try {
				// 1. ����HTTP����
				String url = "http://127.0.0.1:8080/j2me/get.jsp?name=" + name + "&passwd=" + passwd;
				HttpConnection httpConn = (HttpConnection) Connector.open(url);
				
				// 3. �������󷽷�
				httpConn.setRequestMethod(HttpConnection.GET);
				
				// 4. ��ȡ���
				
				
				InputStream is = httpConn.openInputStream();
				
				int len = (int) httpConn.getLength();
				
				byte[] buffer = new byte[len];
				
				is.read(buffer);
				System.out.println("reade form tomcat: " + new String(buffer));
				form.append(new String(buffer));
				
				
				// 2. �ر�����
				httpConn.close();
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
