package com.soft.userinterface;

import javax.microedition.lcdui.Alert;
import javax.microedition.lcdui.AlertType;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Form;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class AlertMIDlet extends MIDlet {
	private Display display;
	private Alert alert;
	private Form form;

	public AlertMIDlet() {
		display = Display.getDisplay(this);
		alert = new Alert("Alert title", "text", null, AlertType.INFO);
		form = new Form("title");
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
//		display.setCurrent(alert);
		display.setCurrent(alert, form);
		int out = alert.getDefaultTimeout();
		System.out.println("out: " + out);
		
		alert.setTimeout(5000);
	}

}
