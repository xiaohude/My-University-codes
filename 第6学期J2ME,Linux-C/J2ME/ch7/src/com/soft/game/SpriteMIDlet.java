package com.soft.game;

import java.io.IOException;

import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.GameCanvas;
import javax.microedition.lcdui.game.Sprite;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class SpriteMIDlet extends MIDlet {
	private Display display;
	private MyGameCanvas gameCanvas;
	
	public SpriteMIDlet() {
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
		
		private int curX;
		private int curY;
		
		private Sprite sprite;
		
		private boolean isRun;
		
		protected MyGameCanvas() {
			super(true);
			
			g = this.getGraphics();
			
			curX = 20;
			curY = 40;
			
			try {
				Image img = Image.createImage("/sprite.png");
				sprite = new Sprite(img);
				sprite.setPosition(curX, curY);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			isRun = true;
			new Thread(this).start();
		}

		// 绘制界面
		private void draw() {
			// 清屏
			g.setColor(255, 255, 255);
			g.fillRect(0, 0, this.getWidth(), this.getHeight());
			
			// 绘制Sprite
			sprite.paint(g);
			
			this.flushGraphics();
		}
		
		// 判断用户的输入，进行逻辑处理
		private void logic() {
			int keyState = this.getKeyStates();
			if ((keyState & GameCanvas.UP_PRESSED) != 0) {
				sprite.move(0, -1);
				this.draw();
			} else if ((keyState & GameCanvas.DOWN_PRESSED) != 0) {
				sprite.move(0, 1);
				this.draw();
			} else if ((keyState & GameCanvas.LEFT_PRESSED) != 0) {
				sprite.move(-1, 0);
				this.draw();
			} else if ((keyState & GameCanvas.RIGHT_PRESSED) != 0) {
				sprite.move(1, 0);
				this.draw();
			} 
			
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
