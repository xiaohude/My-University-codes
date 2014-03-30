package com.soft.case3;

import java.io.IOException;

import javax.microedition.lcdui.Canvas;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;

public class WelCanvas extends Canvas implements CommandListener {
	private MainMIDlet mainMIDlet;
	private Command exitCmd;
	private Command telCmd;
	
	public WelCanvas(MainMIDlet mainMIDlet) {
		this.mainMIDlet = mainMIDlet;
		this.setTitle("Welcome Canvas");
		
		exitCmd = new Command("Exit", Command.EXIT, 1);
		telCmd = new Command("Tel", Command.SCREEN, 1);
		
		this.addCommand(exitCmd);
		this.addCommand(telCmd);
		
		this.setCommandListener(this);
		
	}
	
	protected void paint(Graphics g) {
		g.drawString("Welcome!", 40, 40, Graphics.TOP | Graphics.LEFT);

		
		try {
			Image img = Image.createImage("/wel.png");
			g.drawImage(img, 40, 80, Graphics.TOP | Graphics.LEFT);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == exitCmd) {
			mainMIDlet.exit();
		} else if (cmd == telCmd) {
			mainMIDlet.changeUI(2);
		}
	}

}
