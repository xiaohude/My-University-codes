package com.soft.ui;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ChangeMIDlet extends MIDlet {
	private Display display;
	private Form form;
	private Command changeCmd;
	
	private MyListener cmdListener;
	
	public ChangeMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("form");
		changeCmd = new Command("cmd", Command.SCREEN, 1);
		cmdListener = new MyListener();
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(form);
		form.addCommand(changeCmd);
		form.setCommandListener(cmdListener);

	}

	class MyListener implements CommandListener {
		public MyListener() {
			
		}
		
		public void commandAction(Command cmd, Displayable dis) {
			if (cmd == changeCmd) {
				
			}
			
		}
	}
}


