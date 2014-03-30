package com.soft.case3;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.List;

public class TelList extends List implements CommandListener {
	private MainMIDlet mainMIDlet;
	private Command backCmd;
	private Command addCmd;
	private Command delCmd;
	
	public TelList(MainMIDlet mainMIDlet) {
		super("Tel List", List.EXCLUSIVE);
		this.mainMIDlet = mainMIDlet;
		
		backCmd = new Command("Back", Command.BACK, 1);
		addCmd = new Command("Add", Command.SCREEN, 1);
		delCmd = new Command("Del", Command.SCREEN, 2);
		
		this.addCommand(backCmd);
		this.addCommand(addCmd);
		this.addCommand(delCmd);
		
		this.setCommandListener(this);
		
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == backCmd) {
			mainMIDlet.changeUI(1);
		} else if (cmd == addCmd) {
			mainMIDlet.changeUI(3);
		} else if (cmd == delCmd) {
			
		}
	}

}
