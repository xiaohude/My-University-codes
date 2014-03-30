package com.soft.xiaohu;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.TextField;

public class Third extends Form implements CommandListener
{
    private TextField textField;
    private Command ca;
	private Command et;
	public Third(String title) 
	{
		super(title);
		textField=new TextField("ºÅÂë","",20,10);
		ca = new Command("·µ»Ø", Command.SCREEN, 1);
	    et = new Command("·¢ËÍ", Command.SCREEN, 1);
	}
	public void myAddcommand()
	{
	   this.append(textField);
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
