package com.soft.case3;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.TextField;
import javax.microedition.rms.RecordStore;

public class AddTelForm extends Form implements CommandListener {
	private MainMIDlet mainMIDlet;
	
	private Command okCmd;
	private Command backCmd;
	
	private TextField nameField;
	private TextField telField;
	
	public AddTelForm(MainMIDlet mainMIDlet) {
		super("Add Tel");
		this.mainMIDlet = mainMIDlet;
		
		backCmd = new Command("Back", Command.BACK, 1);
		okCmd = new Command("OK", Command.OK, 1);
		
		this.addCommand(okCmd);
		this.addCommand(backCmd);
		this.setCommandListener(this);
		
		nameField = new TextField("Name:", "", 16, TextField.ANY);
		telField = new TextField("Tel:", "", 16, TextField.PHONENUMBER);
		
		this.append(nameField);
		this.append(telField);
		
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == backCmd) {
			mainMIDlet.changeUI(2);
		} else if (cmd == okCmd) {
			// 将用户输入的数据添加到RMS
			String name = nameField.getString();
			String tel = telField.getString();
			
			// add
			RMSUtil rmsUtil = new RMSUtil();
			rmsUtil.addString(CaseConstant.RS_NAME, name + ":" + tel);
			
			
			// 转换到List界面
			mainMIDlet.changeUI(2);
		}
	}

}
