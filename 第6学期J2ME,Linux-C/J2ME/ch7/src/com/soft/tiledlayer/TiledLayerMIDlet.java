package com.soft.tiledlayer;

import java.io.IOException;

import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.GameCanvas;
import javax.microedition.lcdui.game.Sprite;
import javax.microedition.lcdui.game.TiledLayer;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class TiledLayerMIDlet extends MIDlet {
	private Display display;
	private MyGameCanvas gameCanvas;
	
	public TiledLayerMIDlet() {
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
		
		private TiledLayer tiledLayer;
		
		protected MyGameCanvas() {
			super(true);
			
			g = this.getGraphics();
			
			try {
				Image img = Image.createImage("/map.png");
				
				tiledLayer = new TiledLayer(4, 5, img, img.getWidth() / 2, img.getHeight());
				
				// 1. 逐个填充
				
				// 2. 一维数组
				
				// 3. 二维数组
				
				// 区域填充
				tiledLayer.fillCells(0, 0, 3, 3, 2);
				
				
				
				tiledLayer.setPosition(40, 40);
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			new Thread(this).start();
			
		}

		// 绘制界面
		private void draw() {
			// 清屏
			g.setColor(255, 255, 255);
			g.fillRect(0, 0, this.getWidth(), this.getHeight());
			
			// 绘制
			tiledLayer.paint(g);
			
			
			this.flushGraphics();
		}
		
		// 判断用户的输入，进行逻辑处理
		private void logic() {
			
		}
		
		public void run() {
			this.draw();
		}
	}

}
