package com.soft.gauge;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.Item;
import javax.microedition.lcdui.ItemCommandListener;
import javax.microedition.lcdui.ItemStateListener;
import javax.microedition.lcdui.TextField;
import javax.microedition.lcdui.Ticker;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ItemEventMIDlet extends MIDlet implements ItemCommandListener, ItemStateListener {
	private Display display;
	private Form form;
	private TextField nameField;
	private TextField pwdField;
	private Command delCmd;
	
	private Ticker ticker;
	
	public ItemEventMIDlet() {
		display = Display.getDisplay(this);
		form = new Form("title");
		nameField = new TextField("name", "", 16, TextField.ANY);
		pwdField = new TextField("passwd", "", 16, TextField.PASSWORD);
		delCmd = new Command("Del", Command.SCREEN, 1);
		
		ticker = new Ticker("ticker text content!");
		
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(form);
		form.append(nameField);
		form.append(pwdField);
		
		nameField.addCommand(delCmd);
		nameField.setItemCommandListener(this);
		
		pwdField.addCommand(delCmd);
		pwdField.setItemCommandListener(this);
		
		form.setItemStateListener(this);
		
		form.setTicker(ticker);
		
	}
	
	public void commandAction(Command cmd, Item item) {
		if (cmd == delCmd) {
			if (item == nameField) {
				
			} else if (item == pwdField) {
				
			}
		}
	}
	
	public void itemStateChanged(Item item) {
		System.out.println("item:" + item.getLabel());
	}

}
