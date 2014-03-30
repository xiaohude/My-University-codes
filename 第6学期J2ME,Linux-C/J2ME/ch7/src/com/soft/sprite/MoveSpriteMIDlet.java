package com.soft.sprite;

import java.io.IOException;

import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.GameCanvas;
import javax.microedition.lcdui.game.Sprite;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class MoveSpriteMIDlet extends MIDlet {
	private Display display;
	private MyGameCanvas gameCanvas;
	
	public MoveSpriteMIDlet() {
		display = Display.getDisplay(this);
		gameCanvas = new MyGameCanvas();
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
		// TODO Auto-generated method stub

	}

	protected void pauseApp() {
		// TODO Auto-generated method stub

	}

	protected void startApp() throws MIDletStateChangeException {
		display.setCurrent(gameCanvas);

	}
	
	class MyGameCanvas extends GameCanvas implements Runnable {
		private Graphics g;
		
		private Sprite sprite1;
		private Sprite sprite2;
		
		private boolean isRun;
		
		protected MyGameCanvas() {
			super(true);
			
			g = this.getGraphics();
			
			try {
				Image img1 = Image.createImage("/img1.png");
				sprite1 = new Sprite(img1);
				
				Image img2 = Image.createImage("/img2.png");
				sprite2 = new Sprite(img2);
				sprite2.setPosition(200, 200);
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			// 启动线程
			isRun = true;
			new Thread(this).start();
			
			
		}

		// 绘制界面
		private void draw() {
			// 清屏
			g.setColor(255, 255, 255);
			g.fillRect(0, 0, this.getWidth(), this.getHeight());
			
			sprite1.paint(g);
			sprite2.paint(g);
			
			this.flushGraphics();
		}
		
		// 进行逻辑处理
		private void logic() {
			sprite1.move(1, 1);
			
			sprite2.move(-1, -1);
			
			if(sprite1.collidesWith(sprite2, true)) {
				isRun = false;
				System.out.println("collidesWith!!!!!!");
			}
			
			
			this.draw();
		}
		
		public void run() {
			
			this.draw();
			
			while(isRun) {
				logic();
				
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

}
