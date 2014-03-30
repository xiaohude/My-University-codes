package com.soft.ui;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class UIChangeMIDlet extends MIDlet implements CommandListener {
	private Display display;
	private Form firForm;
	private Form secForm;
	private Command changeCmd;
	
	public UIChangeMIDlet() {
		display = Display.getDisplay(this);
		firForm = new Form("First Form");
		secForm = new Form("Second Form");
		changeCmd = new Command("Chage", Command.SCREEN, 1);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(firForm);
//		display.setCurrent(secForm);
		
		firForm.addCommand(changeCmd);
		firForm.append("dasfjei0");
		firForm.setCommandListener(this);
		
		secForm.addCommand(changeCmd);
		secForm.setCommandListener(this);
	}
	
	/**
	 * 界面转换
	 * @param cmd 
	 * @param dis 
	 */
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == changeCmd) {
			if (dis == firForm) {
				// 转换到第2个界面
				display.setCurrent(secForm);
			} else if (dis == secForm) {
				// 转换到第1个界面
				display.setCurrent(firForm);
			}
		}
		
	}

}
