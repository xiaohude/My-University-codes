package com.soft.canvas;

import javax.microedition.lcdui.Display;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class MyCanvasMIDlet extends MIDlet{
	private Display display;
	private EventCanvas ballCanvas;
	
	
	public MyCanvasMIDlet() {
		display = Display.getDisplay(this);
		ballCanvas = new EventCanvas();
		
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		
		display.setCurrent(ballCanvas);
	
	}

}
