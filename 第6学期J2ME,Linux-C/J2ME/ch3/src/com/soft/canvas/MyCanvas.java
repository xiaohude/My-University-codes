package com.soft.canvas;

import javax.microedition.lcdui.Canvas;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Graphics;

public class MyCanvas extends Canvas implements CommandListener {
	// ��λ����
	private int curY;
	private int curX;
	
	// ״̬�����������˶�����
	// 0 �����½�  1��������
	private int directionY;
	
	// 0���� �� 1���� ��
	private int directionX;
	
	// ���� �����˶����
	private Command startCmd;
	private Command stopCmd;
	
	// �߳�״̬����
	// true �߳�����; false �߳�ֹͣ
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
		
		// �����߳�
		new Thread(new BallThread()).start();
	}

	protected void paint(Graphics g) {
		// ����
		g.setColor(255, 255, 255);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
		
		// ����ͼ��ͼ��
		g.setColor(255, 0, 0);
		g.fillArc(curX, curY, 60, 60, 0, 360);
		
		
	}
	
	public void commandAction(Command cmd, Displayable dis) {
		if (cmd == startCmd) {
			// ����
			isRuning = true;
			
			new Thread(new BallThread()).start();
			
			// �ı䰴ť��ʾ
			this.removeCommand(startCmd);
			this.addCommand(stopCmd);
			
		} else if (cmd == stopCmd) {
			// ��ͣ
			isRuning = false;
			
			// �ı䰴ť��ʾ
			this.removeCommand(stopCmd);
			this.addCommand(startCmd);
		}
		
	}
	
	class BallThread implements Runnable {
		// �߳�ʵ��
		public void run() {
			// ѭ������
			while(isRuning) {
				// �жϷ��򲢸ı�X����
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
					// �����˶�
					
					// �ı�Y����
					if (curY + 60 < getHeight()) {
						curY++;
					} else {
						directionY = 1;
					}
				} else if (directionY == 1) {
					// �����˶�
					if (curY > 0) {
						curY--;
					} else {
						directionY = 0;
					}
				}				
				
				
				// �ػ�
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
