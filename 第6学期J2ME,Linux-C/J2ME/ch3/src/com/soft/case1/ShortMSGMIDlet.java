package com.soft.case1;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ShortMSGMIDlet extends MIDlet implements CommandListener {
	private Display display;
	
	// 第1个界面
	private Form welForm;
	private Command exitCmd;
	private Command enterEditCmd;
	
	// 第2个界面
	private Form editForm;
	private TextField contentField;
	private Command backWelCmd;
	private Command enterSendCmd;
	
	// 第3个界面
	private Form sendForm;
	private TextField telNoField;
	private Command sendCmd;
	private Command backEditCmd;
	
	
	public ShortMSGMIDlet() {
		// 初始化
		display = Display.getDisplay(this);
		
		// 第1个界面的初始化
		
		// 第2个界面的初始化
		
		// 第3个界面的初始化
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == exitCmd) {
			// 退出
			
		} else if (cmd == enterEditCmd) {
			// 进入到第2个界面 编辑界面
			
		} else if (cmd == backWelCmd) {
			// 返回到第1个界面 欢迎界面
			
		} else if (cmd == enterSendCmd) {
			// 进入到第3个界面 发送界面
			
		} else if (cmd == backEditCmd) {
			// 返回到第2个界面 编辑界面
			
		} else if (cmd == sendCmd) {
			// 发送
		}
		
	}

}
