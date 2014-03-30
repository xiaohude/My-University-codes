package com.soft.screen;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.TextBox;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class TextBoxMIDlet extends MIDlet {
	private Display display;
	private TextBox textBox;
	private Command getCmd;
	private Command delCmd;
	
	public TextBoxMIDlet() {
		display = Display.getDisplay(this);
		textBox = new TextBox("text box", "", 140, TextField.ANY);
		getCmd = new Command("Get", Command.SCREEN, 1);
		delCmd = new Command("Del", Command.CANCEL, 1);
		
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(textBox);
		
		textBox.addCommand(getCmd);
		textBox.addCommand(delCmd);
		
		textBox.setCommandListener(new CommandListener() {
			public void commandAction(Command cmd, Displayable arg1) {
				if (cmd == getCmd) {
					System.out.println("text: " + textBox.getString());
				} else if (cmd == delCmd) {
					int pos = textBox.getCaretPosition();
					if (pos >= 1 ) {
						textBox.delete(pos - 1, 1);
					}
					
					
				}
				
			}
		});
	}

}
