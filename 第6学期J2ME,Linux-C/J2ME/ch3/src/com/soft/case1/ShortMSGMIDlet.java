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
	
	// ��1������
	private Form welForm;
	private Command exitCmd;
	private Command enterEditCmd;
	
	// ��2������
	private Form editForm;
	private TextField contentField;
	private Command backWelCmd;
	private Command enterSendCmd;
	
	// ��3������
	private Form sendForm;
	private TextField telNoField;
	private Command sendCmd;
	private Command backEditCmd;
	
	
	public ShortMSGMIDlet() {
		// ��ʼ��
		display = Display.getDisplay(this);
		
		// ��1������ĳ�ʼ��
		
		// ��2������ĳ�ʼ��
		
		// ��3������ĳ�ʼ��
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
			// �˳�
			
		} else if (cmd == enterEditCmd) {
			// ���뵽��2������ �༭����
			
		} else if (cmd == backWelCmd) {
			// ���ص���1������ ��ӭ����
			
		} else if (cmd == enterSendCmd) {
			// ���뵽��3������ ���ͽ���
			
		} else if (cmd == backEditCmd) {
			// ���ص���2������ �༭����
			
		} else if (cmd == sendCmd) {
			// ����
		}
		
	}

}
