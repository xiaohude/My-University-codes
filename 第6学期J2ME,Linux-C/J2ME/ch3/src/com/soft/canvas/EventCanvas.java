package com.soft.canvas;

import java.io.IOException;

import javax.microedition.lcdui.Canvas;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;

public class EventCanvas extends Canvas {
	private int curX;
	private int curY;
	public EventCanvas() {
		curX = 60;
		curY = 70;
	}

	protected void paint(Graphics g) {
	
		// «Â∆¡
		g.setColor(255, 255, 255);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
		
		
		try {
			Image img = Image.createImage("/Duke1.png");
			g.drawImage(img, curX, curY, Graphics.LEFT | Graphics.TOP);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	protected void keyPressed(int keyCode) {
		
		int gameAction = this.getGameAction(keyCode);

		switch (gameAction) {
		case Canvas.UP:
			curY--;
			break;
		case DOWN:
			curY++;
			break;
		case LEFT:
			curX--;
			break;
		case RIGHT:
			curX++;
			break;

		default:
			break;
		}
		
		repaint();
	}

	protected void keyReleased(int keyCode) {
		
	}

	protected void keyRepeated(int keyCode) {
		this.keyPressed(keyCode);
	}
}
