#ifndef INCLUDE_GRAFX
#define INCLUDE_GRAFX

#include <libndls.h>
#include <stdarg.h>

#define GRAFX_min(a, b) ((a) < (b) ? (a) : (b))
#define GRAFX_max(a, b) ((a) > (b) ? (a) : (b))

typedef int Fixed;
typedef struct
{
	int x;
	int y;
	int h;
	int w;
} Rect;

#define itofix(x) ((x) << 8)
#define fixtoi(x) ((x) >> 8)
#define fixdiv(x, y) (((x) << 8) / (y))
#define clamp(x, a, b) GRAFX_min(GRAFX_max(x, a), b)
#define sign(x) ((x) < 0)
#define fixsin(x) fixcos((x) - 64)

#ifdef __cplusplus
extern "C" {
#endif

extern Fixed fixmul(Fixed x, Fixed y);
extern Fixed fixcos(Fixed angle);
extern void rotate(int x, int y, int cx, int cy, Fixed angle, Rect* out);
extern void getBoundingBox(int x, int y, int w, int h, int cx, int cy, Fixed angle, Rect *out);
extern int sq(int);
extern Fixed fixsq(Fixed);
extern int cube(int);
extern Fixed fixcube(Fixed);
extern int interpolatePathFixed(Fixed[], Fixed[], int[], int, Rect*);
extern int interpolatePathFloat(float[], float[], int[], int, Rect*);

extern void initBuffering();
extern void updateScreen();
extern void deinitBuffering();
extern void timer_init(unsigned);
extern void timer_restore(unsigned);
extern void timer_load(unsigned, unsigned);
extern unsigned timer_read(unsigned);
extern void clearBufferB();
extern void clearBufferW();
extern void clearBuffer(unsigned short);
extern unsigned short getPixel(const unsigned short*, unsigned int, unsigned int);
extern void setPixelUnsafe(unsigned int, unsigned int, unsigned short);
extern void setPixel(unsigned int, unsigned int, unsigned short);
extern void setPixelRGB(unsigned int, unsigned int, unsigned char, unsigned char, unsigned char);
extern void drawHLine(int, int, int, unsigned short);
extern void drawVLine(int, int, int, unsigned short);
extern void fillRect(int, int, int, int, unsigned short);
extern void drawSprite(const unsigned short*, int, int, int, unsigned short);
extern void drawSpritePart(const unsigned short*, int, int, const Rect*, int, unsigned short);
extern void drawSpriteScaled(const unsigned short*, const Rect*, int, unsigned short);
extern void drawSpriteRotated(const unsigned short*, const Rect*, const Rect*, Fixed, int, unsigned short);
extern void drawLine(int, int, int, int, unsigned short);
extern void drawPolygon(unsigned short, int, ...);
extern void fillCircle(int, int, int, unsigned short);
extern void fillEllipse(int, int, int, int, unsigned short);
extern void drawString(int*, int*, int, const char*, unsigned short, unsigned short);
extern void drawDecimal(int*, int*, int, unsigned short, unsigned short);
extern void drawChar(int*, int*, int, char, unsigned short, unsigned short);
extern void drawStringF(int*, int*, int, unsigned short, unsigned short, const char*, ...);
extern int numberWidth(int);
extern int stringWidth(const char*);
extern int get_key_pressed(t_key*);
extern int isKey(t_key, t_key);

extern unsigned short * loadBMP(const char*, unsigned short);

#define BUFF_BYTES_SIZE (320*240*2)
extern unsigned short *BUFF_BASE_ADDRESS;
#ifdef __cplusplus
}
#endif

#endif
