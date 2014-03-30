package com.soft.xiaohu;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.TextBox;

public class Second extends TextBox implements CommandListener
{
	private Command ca;
	private Command et;
	public Second(String title, String text, int maxSize, int constraints)
	{
		super(title, text, maxSize, constraints);
		ca = new Command("·µ»Ø", Command.SCREEN, 1);
	    et = new Command("È·¶¨", Command.SCREEN, 1);
		
	}
	public void myAddcommand()
	{
	   this.addCommand(ca);
	   this.addCommand(et);
	   this.setCommandListener(this);
	}
	public void commandAction(Command cmd, Displayable arg1)
	{
		if(cmd==ca)
		{
			
		}
		else if(cmd==et)
		{
			
		}
		
	}

}
