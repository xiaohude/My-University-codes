package com.soft.gauge;

import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.Gauge;
import javax.microedition.lcdui.Spacer;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class GaugeMIDlet extends MIDlet {
	private Display display;
	private Form form;
	private Gauge gauge;
	private Spacer spacer;
	
	public GaugeMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("form");
		gauge = new Gauge("gauge", false, 100, 20);
		spacer = new Spacer(80, 40);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(form);
		
		form.append(gauge);
		
//		form.append(spacer);
		
		form.append("sdjkfljasieu");
		
		// Æô¶¯Ïß³Ì
		new Thread(new GaugeThread()).start();
		
	}
	
	class GaugeThread implements Runnable {
		private boolean isRun;
		
		public GaugeThread() {
			isRun = true;
		}
		
		public void run() {
			
			while(isRun) {
				System.out.println("thread running");
				int val = gauge.getValue();
				if (val < gauge.getMaxValue()) {
					gauge.setValue(val + 1);
				} else {
					isRun = false;
				}
				
				try {
					Thread.currentThread().sleep(50);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

}
