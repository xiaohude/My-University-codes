package com.soft.item;

import java.util.Calendar;
import java.util.Date;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.DateField;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ItemsMIDlet extends MIDlet {
	private Display display;
	private Form form;
	
	private Command xCmd;
	
	private DateField dateField;

	public ItemsMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("form title");
		
		xCmd = new Command("X", Command.SCREEN, 1);
	
		dateField = new DateField("date", DateField.DATE_TIME);
		
		
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(form);

		form.append(dateField);
		
		form.addCommand(xCmd);
		
		form.setCommandListener(new CommandListener() {
			public void commandAction(Command cmd, Displayable arg1) {
				if (cmd == xCmd) {
					Date date = dateField.getDate();
					
					Calendar calendar = Calendar.getInstance();
					
					calendar.setTime(date);
					
					int year = calendar.get(Calendar.MONTH);
					System.out.println("year: " + year);
				}
			}
		});
	}

}
