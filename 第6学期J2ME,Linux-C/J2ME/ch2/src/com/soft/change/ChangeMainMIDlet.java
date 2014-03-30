package com.soft.change;

import javax.microedition.lcdui.Display;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ChangeMainMIDlet extends MIDlet {
	private Display display;
	private FirstForm firForm;
	private SecondForm secForm;
	
	public ChangeMainMIDlet() {
		display = Display.getDisplay(this);
		firForm = new FirstForm(this);
		secForm = new SecondForm(this);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(firForm);
	}
	
	public void changeUI(int index) {
		switch (index) {
		case 1:
			display.setCurrent(firForm);
			break;
		case 2:
			display.setCurrent(secForm);
			break;

		default:
			break;
		}
	}

}
