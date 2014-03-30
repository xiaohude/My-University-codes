package com.soft.screen;

import javax.microedition.lcdui.Choice;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.List;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class ListMIDlet extends MIDlet implements CommandListener {
	private Display display;
	private List list;
	private Command getCmd;

	public ListMIDlet() {
		display = Display.getDisplay(this);
		list = new List("list:", Choice.MULTIPLE);
		getCmd = new Command("Get", Command.SCREEN, 1);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(list);

		list.append("item1", null);
		list.append("item2", null);
		list.append("item3", null);
		list.append("item4", null);
		
		
		list.addCommand(getCmd);
		list.setCommandListener(this);

	}

	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == getCmd) {
			int size = list.size();
			
			boolean[] flags = new boolean[size];
			
			list.getSelectedFlags(flags);
			
			for(int i = 0; i < size; i++) {
				if(flags[i]) {
					System.out.println("index: " + i + " string: " + list.getString(i));
				}
			}
			
		}

	}

}
