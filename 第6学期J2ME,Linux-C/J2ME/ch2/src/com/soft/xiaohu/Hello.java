package com.soft.xiaohu;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;

public class Hello extends Form implements CommandListener
{
	
	private Command ca;
	private Command et;

	public Hello(String title) 
	{
		super(title);
	    
       ca = new Command("ÍË³ö", Command.SCREEN, 1);
       et = new Command("Ð´¶ÌÐÅ", Command.SCREEN, 1);
	}
	public void myAddcommand()
	{
	   this.addCommand(ca);
	   this.addCommand(et);
	   this.setCommandListener(this);
	}
	public void commandAction(Command cmd, Displayable tCmd) 
	{
		if(cmd==ca)
		{
			
		}
		else if(cmd==et)
		{
			
		}
		
	}

}
