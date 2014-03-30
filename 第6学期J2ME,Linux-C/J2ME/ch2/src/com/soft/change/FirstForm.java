package com.soft.change;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;

public class FirstForm extends Form implements CommandListener {
	private ChangeMainMIDlet mainMIDlet;
	private Command changeCmd;
	
	public FirstForm(ChangeMainMIDlet mainMIDlet) {
		super("First Form Title");
		
		this.mainMIDlet = mainMIDlet;
		
		changeCmd = new Command("Change to 2", Command.SCREEN, 1);
		
		this.addItems();
	}
	
	private void addItems() {
		this.addCommand(changeCmd);
		this.setCommandListener(this);
	}
	
	
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == changeCmd) {
			// ����MainMIDlet�Ĵ��룬ת������2������
			mainMIDlet.changeUI(2);
			
		}
		
	}

}
