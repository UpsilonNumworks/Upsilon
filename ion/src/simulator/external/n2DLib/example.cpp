#include "n2DLib.h"

#define UNUSED(var) (void)var

int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	Fixed theta = 0;
	Rect spr, nullRect = {0, 0, 0, 0};
	Rect pt1, pt2;
	Fixed ax[] = { 300, 260, 220, 280 }, ay[] = { 10, 120 , 30, 80 }, at[] = { 0, 16, 24, 36 };
	float fax[] = { 200., 160., 120., 180. }, fay[] = { 10., 120. , 30., 80. };
	
	int x, y, i;
	
	enable_relative_paths(argv);
	
	unsigned short *sprite = loadBMP("example.bmp.tns", 0xf81f);
	if(!sprite)
	{
		printf("Error while loading sprite. Make sure you have example.bmp.tns in the same directory\n");
		return 0;
	}
	
	initBuffering();
	clearBufferB();
	
	spr.x = 160;
	spr.y = 120;
	
	t_key quitKey;
	
	x = y = 0;
	
	drawString(&x, &y, 0, "What key to exit the program ?", 0xffff, 0);
	updateScreen();
	
	while(!get_key_pressed(&quitKey));
	wait_no_key_pressed();
	
	clearBufferB();
	
	while(!isKeyPressed(quitKey))
	{
		fillCircle(160, 120, 80, 0xf800);
		fillEllipse(160, 120, 70, 60, 0x001f);
		drawPolygon(0x07e0, 4, 140, 100, 180, 100, 180, 140, 140, 140);
		drawHLine(80, -10, 330, 0xf800);
		drawHLine(160, -10, 330, 0xf800);
		drawVLine(106, -10, 250, 0xf800);
		drawVLine(212, -10, 250, 0xf800);
		
		fillRect(-10, -10, 20, 20, 0xf800);
		fillRect(310, -10, 20, 20, 0x07e0);
		fillRect(310, 230, 20, 20, 0x001f);
		fillRect(-10, 230, 20, 20, 0xffff);
		
		x = 0;
		y = 120;
		
		drawString(&x, &y, x, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqsrtuvwxyz\n0123456789<!%$#>\n", 0, 0xffff);
		drawDecimal(&x, &y, -2134567841, 0x07e0, 0xf800);
		x = 0;
		y += 8;
		drawStringF(&x, &y, x, 0x07e0, 0xf800, "Test ; number : %d\nstring : %s", 42, "the game");
		
		spr.w = theta / 2;
		spr.h = theta / 2;
		drawSpriteScaled(sprite, &spr, 0, 0); // don't flash
		drawSpriteRotated(sprite, &spr, &nullRect, theta, theta < 128, 0xffff); // occasionally flash
		theta++;
		theta &= 255;
		
		updateScreen();
	}
	
	clearBufferB();
	
	wait_no_key_pressed();
	
	while(!isKeyPressed(quitKey))
	{
		for(i = 0; i < 4; i++)
		{
			fillRect(ax[i]-2, ay[i]-2, 5, 5, 0xf800);
			fillRect(fax[i]-2, fay[i]-2, 5, 5, 0xf800);
		}
		
		interpolatePathFloat(fax, fay, at, 4, &pt1);
		
		while(!interpolatePathFloat(fax, fay, at, 4, &pt2))
		{
			drawLine(pt1.x, pt1.y, pt2.x, pt2.y, 0x07f0);
			pt1 = pt2;
		}
		drawLine(pt1.x, pt1.y, pt2.x, pt2.y, 0x07f0);
		
		interpolatePathFixed(ax, ay, at, 4, &pt1);
		
		while(!interpolatePathFixed(ax, ay, at, 4, &pt2))
		{
			drawLine(pt1.x, pt1.y, pt2.x, pt2.y, 0xffff);
			pt1 = pt2;
		}
		drawLine(pt1.x, pt1.y, pt2.x, pt2.y, 0xffff);
		updateScreen();
	}
	deinitBuffering();
	
	return 0;
}
