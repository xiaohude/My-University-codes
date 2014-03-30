package com.soft.game;

import java.io.IOException;

import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.GameCanvas;
import javax.microedition.lcdui.game.Sprite;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class SpriteTranMIDlet extends MIDlet {
	private Display display;
	private MyGameCanvas gameCanvas;
	
	public SpriteTranMIDlet() {
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
		
		private int tran;
		
		private boolean isRun;
		
		protected MyGameCanvas() {
			super(true);
			
			g = this.getGraphics();
			
			curX = 20;
			curY = 40;
			
			try {
				Image img = Image.createImage("/monkey.png");
				sprite = new Sprite(img);
			
				// 定义悬挂点
				sprite.defineReferencePixel(25, 3);
				// 设置悬挂位置
				sprite.setRefPixelPosition(curX + sprite.getWidth(), curY);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			tran = Sprite.TRANS_NONE;
			
			isRun = true;
			new Thread(this).start();
		}

		// 绘制界面
		private void draw() {
			// 清屏
			g.setColor(255, 255, 255);
			g.fillRect(0, 0, this.getWidth(), this.getHeight());
			
			
			g.setColor(255, 0, 0);
			g.drawLine(0, 0, curX + sprite.getWidth(), curY);
			
			// 绘制Sprite
			sprite.paint(g);
			
			this.flushGraphics();
		}
		
		// 进行逻辑处理
		private void logic() {
			switch (tran) {
			case Sprite.TRANS_NONE:
				tran = Sprite.TRANS_ROT90;
				break;
			case Sprite.TRANS_ROT90:
				tran = Sprite.TRANS_ROT180;
				break;
			case Sprite.TRANS_ROT180:
				tran = Sprite.TRANS_ROT270;
				break;
			case Sprite.TRANS_ROT270:
				tran = Sprite.TRANS_NONE;
				break;

			default:
				break;
			}
			
			sprite.setTransform(tran);
			this.draw();
		}
		
		public void run() {
			this.draw();
			
			while(isRun) {
				logic();
				
				try {
					Thread.sleep(400);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

}
