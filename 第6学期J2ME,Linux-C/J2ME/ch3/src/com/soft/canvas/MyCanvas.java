package com.soft.canvas;

import javax.microedition.lcdui.Canvas;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Graphics;

public class MyCanvas extends Canvas implements CommandListener {
	// 定位坐标
	private int curY;
	private int curX;
	
	// 状态变量，定义运动方向
	// 0 代表下降  1代表上升
	private int directionY;
	
	// 0代表 左； 1代表 右
	private int directionX;
	
	// 命令 控制运动与否
	private Command startCmd;
	private Command stopCmd;
	
	// 线程状态变量
	// true 线程运行; false 线程停止
	private boolean isRuning;
	
	public MyCanvas() {
		this.setTitle("canvas title");
		curY = 0;
		curX = 80;
		directionY = 0;
		directionX = 0;
		
		startCmd = new Command("Start", Command.SCREEN, 1);
		stopCmd = new Command("Stop", Command.SCREEN, 1);
		
		this.addCommand(stopCmd);
		this.setCommandListener(this);
		
		
		isRuning = true;
		
		// 启动线程
		new Thread(new BallThread()).start();
	}

	protected void paint(Graphics g) {
		// 清屏
		g.setColor(255, 255, 255);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
		
		// 画出图形图像
		g.setColor(255, 0, 0);
		g.fillArc(curX, curY, 60, 60, 0, 360);
		
		
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == startCmd) {
			// 运行
			isRuning = true;
			
			new Thread(new BallThread()).start();
			
			// 改变按钮显示
			this.removeCommand(startCmd);
			this.addCommand(stopCmd);
			
		} else if (cmd == stopCmd) {
			// 暂停
			isRuning = false;
			
			// 改变按钮显示
			this.removeCommand(stopCmd);
			this.addCommand(startCmd);
		}
		
	}
	
	class BallThread implements Runnable {
		// 线程实现
		public void run() {
			// 循环控制
			while(isRuning) {
				// 判断方向并改变X坐标
				if (directionX == 0) {
					if (curX > 0) {
						curX--;
					} else {
						directionX = 1;
					}
					
				} else if (directionX == 1) {
					if (curX + 60 < getWidth()) {
						curX++;
					} else {
						directionX = 0;
					}
					
				}
				
				if (directionY == 0) {
					// 向下运动
					
					// 改变Y坐标
					if (curY + 60 < getHeight()) {
						curY++;
					} else {
						directionY = 1;
					}
				} else if (directionY == 1) {
					// 向上运动
					if (curY > 0) {
						curY--;
					} else {
						directionY = 0;
					}
				}				
				
				
				// 重画
				repaint();
				
				try {
					Thread.currentThread().sleep(5);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		} // end of while
	} // end of run
}
