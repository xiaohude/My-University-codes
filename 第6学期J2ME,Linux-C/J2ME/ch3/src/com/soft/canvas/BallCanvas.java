package com.soft.canvas;

import javax.microedition.lcdui.Canvas;
import javax.microedition.lcdui.Graphics;

public class BallCanvas extends Canvas {

	// ��λ����
	private int curY;
	private int curX;
	
	// ״̬�����������˶�����
	// 0 �����½�  1��������
	private int directionY;
	
	// 0���� �� 1���� ��
	private int directionX;
	
	public BallCanvas() {
		this.setTitle("canvas title");
		curY = 0;
		curX = 80;
		directionY = 0;
		directionX = 0;
		
		// �����߳�
		new Thread(new BallThread()).start();
	}
	
	protected void paint(Graphics g) {
		// ����
		g.setColor(255, 255, 255);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
		
		// ����ͼ��ͼ��
		g.setColor(0, 0, 255);
		g.fillArc(curX, curY, 60, 60, 0, 360);
	}
	
	class BallThread implements Runnable {
		public void run() {
			while (true)
			{
				while(curY<getHeight()-60) {
					curY++;
					repaint();
					try {
						Thread.currentThread().sleep(5);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
					
				while(curY>0) {
					curY--;
					repaint();
					try {
						Thread.currentThread().sleep(5);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				
				
				
				
			}
		}
	}

}
