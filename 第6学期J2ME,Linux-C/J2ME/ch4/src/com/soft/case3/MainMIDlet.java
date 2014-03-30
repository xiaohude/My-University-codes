package com.soft.case3;

import javax.microedition.lcdui.Display;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class MainMIDlet extends MIDlet {
	private Display display;
//	private WelForm welForm;
	private WelCanvas welCanvas;
	private TelList telList;
	private AddTelForm addTelForm;
	
	public MainMIDlet() {
		display = Display.getDisplay(this);
//		welForm = new WelForm(this);
		welCanvas = new WelCanvas(this);
		telList = new TelList(this);
		addTelForm = new AddTelForm(this);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
//		display.setCurrent(welForm);
		display.setCurrent(welCanvas);

	}
	
	public void changeUI(int index) {
		switch (index) {
		case 1:
			display.setCurrent(welCanvas);
			break;
		case 2:
			display.setCurrent(telList);
			break;
		case 3:
			display.setCurrent(addTelForm);
			break;
		default:
			break;
		}
	}
	
	public void exit() {
		try {
			this.destroyApp(false);
		} catch (MIDletStateChangeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		this.notifyDestroyed();
	}

}
