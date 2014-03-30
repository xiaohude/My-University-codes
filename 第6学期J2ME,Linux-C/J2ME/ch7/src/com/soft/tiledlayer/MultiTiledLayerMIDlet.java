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

public class MultiTiledLayerMIDlet extends MIDlet {
	private Display display;
	private MyGameCanvas gameCanvas;
	
	public MultiTiledLayerMIDlet() {
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
		
		private TiledLayer tiledLayer1;
		private TiledLayer tiledLayer2;
		
		protected MyGameCanvas() {
			super(true);
			
			g = this.getGraphics();
			
			try {
				Image img = Image.createImage("/map.png");
				
				tiledLayer1 = new TiledLayer(4, 5, img, img.getWidth() / 2, img.getHeight());
				
				tiledLayer2 = new TiledLayer(4, 5, img, img.getWidth() / 2, img.getHeight());
				
				int[][] cells1 = {
					{1, 0, 1, 0},
					{1, 0, 1, 0},
					{1, 0, 1, 0},
					{1, 0, 1, 0},
					{1, 0, 1, 0}
				};
				
				int[][] cells2 = {
						{0, 2, 0, 2},
						{0, 2, 0, 2},
						{0, 2, 0, 2},
						{0, 2, 0, 2},
						{0, 2, 0, 2}
				};
				
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 4; j++) {
						tiledLayer1.setCell(j, i, cells1[i][j]);
						tiledLayer2.setCell(j, i, cells2[i][j]);
					}
				}
				
				
				
				tiledLayer1.setPosition(40, 40);
				
				tiledLayer2.setPosition(40, 40);
				
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
			tiledLayer1.paint(g);
			tiledLayer2.paint(g);
			
			
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
