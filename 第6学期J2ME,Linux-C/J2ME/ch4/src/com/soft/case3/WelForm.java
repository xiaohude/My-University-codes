package com.soft.case3;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;

public class WelForm extends Form implements CommandListener {
	private MainMIDlet mainMIDlet;
	private Command exitCmd;
	private Command telCmd;
	
	public WelForm(MainMIDlet mainMIDlet) {
		super("Welcome Form");
		this.mainMIDlet = mainMIDlet;
		exitCmd = new Command("Exit", Command.EXIT, 1);
		telCmd = new Command("Tel", Command.SCREEN, 1);
		
		this.addCommand(exitCmd);
		this.addCommand(telCmd);
		
		this.setCommandListener(this);
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == exitCmd) {
			mainMIDlet.exit();
		} else if (cmd == telCmd) {
			mainMIDlet.changeUI(2);
		}
	}
	
	
	
	
	
}
