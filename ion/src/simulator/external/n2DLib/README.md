n2DLib documentation
====================

n2DLib is a C graphics library for the TI-Nspire calculators intended to be used with the Ndless 3rd-party jailbreak.

The lib uses buffering to display smoothly ; that means that all drawing is done to a separate buffer in memory which is then copied to the screen.

All colors, unless specified, must be in R5G6B5 format, meaning a 16-bits number organized this way :

Bit   | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 
------|----|----|----|----|----|----|---|---|---|---|---|---|---|---|---|---
Color | R  | R  | R  | R  | R  | G  | G | G | G | G | G | B | B | B | B | B 

n2DLib uses a variation on the NTI image format to store images. All images must be arrays of unsigned short organized this way :

Entry |        0       |        1       |         2       |   3-...
------|----------------|----------------|-----------------|----------
Use   | Width in pixels|Height in pixels|Transparent color|Image data

n2DLib also offers the Rect structure that has four members : x, y, w and h. You're free to use it for various purposes.

About fixed-point numbers
=========================

In addition to graphical commands, n2DLib offers a fast alternative to floating-point numbers that is 24.8 fixed-point numbers. Those numbers are integers whose bits 0-7 are treated like a decimal part, and whose bits 8-24 are treated like an integer part. That means 256 is actually 1.0 when used with the appropriate commands. FIxed-point angles are written in binary angles, meaning a full period is [0, 256].

Since fixed-point numbers are special numbers, they can't interact normally with integers. The following array describes what you can and can't do normally :

           |integer|fixed-point|
-----------|-------|-----------|
integer    |  +-*/ |     *     |
fixed-point|   */  |     +-    |

You need a special routine to :
add an integer to a fixed-point number
divide an integer by a fixed-point number
multiply a fixed-point number by another fixed-point number
divide a fixed-point number by another fixed-point number

See the "Math routines" part of the doc to find how to do all of this.

Using the key detection functions
=================================

n2DLib provides additional key detection functions to those already provided by Ndless, and aims for full compatibility with those latters. That's why n2DLib uses Ndless's t_key struct :

```C
typedef struct {
int row, col, tpad_row, tpad_col;
tpad_arrow_t tpad_arrow;
} t_key;
```

Each key is stored depending on its position on the Nspire's keypad, row and column. You can see two different versions for each variable ; that's because the clickpad keypad and the touchpad keypad have different keymappings. This is taken care of by n2DLib internally, so you don't have to worry about it.

For more info about how the keypad(s) work(s), see http://hackspire.unsads.com/wiki/index.php/Keypads .

See the "Key detection functions" part of the doc to see what you can do. You don't necessarily need these routines unless you want to do specific things like custom keybinding, since what Ndless provides is enough for most cases .

Summary of commands
===================

GRAPHICAL ROUTINES
==================

```C
void clearBufferB()
```

Fills the buffer with black color.

```C
void clearBufferW()
```

Fills the buffer with white color.

```C
void clearBuffer(unsigned short c)
```

Fills the buffer with the given color.

```C
unsigned short getPixel(unsigned short *src, unsigned int x, unsigned int y)
```

Returns the color of a given pixel in an image, or the transparent color of this image if the coordinates given are out-of-bounds.

```C
void deinitBuffering()
```

Frees memory used by the buffering functionalities. Call this as the very last instruction of your program (excepting return).

```C
void drawLine(int x1, int y1, int x2, int y2, unsigned short c)
```

Draws a line between two points of the given color.

```C
void drawPolygon(unsigned short c, int pointsNb, ...)
```

Draws a wired polygon of the given color using a list of pointsNb coordinates (first x, then y).

```C
void drawSprite(unsigned short *src, unsigned int _x, unsigned int _y)
```

Draws an image to the given coordinates.

```C
void drawSpritePart(unsigned short *src, unsigned int _x, unsigned int _y, Rect* part)
```

Draws part of an image to the given coordinates. The routine draws what of the sprite is in the rectangle given by Rect* part.

```C
void drawSpriteRotated(unsigned short* source, Rect* sr, Rect* rc, Fixed angle)
```

Draws a sprite rotated by a given angle at the coordinates given by Rect* sr, so that the rotation of the sprite is performed around the point Rect *rc, which is relative to the sprite itself. The center of the rotation will always be displayed at the coordinates Rect* sr. For example, if rc->x and rc->y are half the sprite's width and height, the sprite will be rotated around its center. You can also pass NULL as Rect* rc to rotate the image around its center.

```C
void drawSpriteScaled(unsigned short* source, Rect* info)
```

Draws a sprite by scaling it so that it fits perfectly in the rectangle given by Rect* info.

```C
void fillCircle(int x, int y, int radius, unsigned short c)
```

Fills a circle of the given color.

```C
void fillEllipse(int x, int y, int w, int h, unsigned short c)
```

Fills an ellipse of the given size with the given color.

```C
void fillRect(int x, int y, int w, int h, unsigned short c)
```

Fills a rectangle of the given dimensions with the given color ; does clipping.

```C
void initBuffering()
```

Initializes the buffering functionalities. Call this as the very first instruction of your program if you want to use n2DLib's buffering.

```C
void setPixel(unsigned int x, unsigned int y, unsigned short c)
```

Sets a pixel to the given color after verifying the pixel is actually in the screen's dimensions.

```C
void setPixelRGB(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
```

Sets a pixel to the given color after verifying the pixel is actually in the screen's dimensions and using three color components.

```C
void setPixelUnsafe(unsigned int x, unsigned int y, unsigned short c)
```

Sets a pixel to the given color, but does not make sure the pixel is in the screen's dimensions. Faster than setPixel, but use only if you know you can't draw out of the screen.

```C
void updateScreen()
```

Copies the content of the buffer to the screen. This does not clear the buffer.

TEXT ROUTINES
=============

```C
void drawChar(int *x, int *y, int margin, char ch, unsigned short fc, unsigned short olc)
```

Draws a single character at the given position with the given front and outline color using n2DLib's built-in font. Does clipping and supports newlines with \n. When \n is passed as ch, the function resets the X value to the passed margin value and Y goes to newline. X and Y are modified like a cursor position would.

```C
void drawDecimal(int *x, int *y, int n, unsigned short fc, unsigned short olc)
```

Draws a signed integer at the given position with the given front and outline color using n2DLib's built-in font. Does clipping. X and Y are modified like a cursor position would. Use this as a fast way to display integers only.

```C
void drawString(int *x, int *y, int margin, const char *str, unsigned short fc, unsigned short olc)
```

Draws a string of characters at the given position with the given front and outline color using n2DLib's built-in font. Does clipping and supports newlines with \n. When \n is encountered in the string, the function resets the X value to the passed margin value and Y goes to newline. X and Y are modified like a cursor position would. Use this as a fast way to display strings only.

```C
void drawStringF(int *x, int *y, int margin, unsigned short fc, unsigned short olc, const char *s, ...)
```

Draws a string of characters at the given position with the given front and outline color using n2DLib's built-in font. Does clipping and supports newlines with \n and printf-like arguments. When \n is encountered in the string, the function resets the X value to the passed margin value and Y goes to newline. X and Y are modified like a cursor position would.

```C
int stringWidth(const char* s)
```

Returns the width of the string in pixels when using n2DLib's built-in font.

```C
int numberWitdh(int n)
```

Returns the width of the decimal in pixels when drawn to the screen using n2DLib's built-in font.


MATH ROUTINES
=============

```C
Type clamp(Type x, Type lowerBound, Type upperBound)
```

Returns x if it's in the interval formed by [lowerBound, upperBound], else returns the corresponding bound.

```C
Fixed fixcos(Fixed angle)
```

Returns the cosinus of a binary angle in fixed-point format.

```C
Fixed fixdiv(Fixed a, Fixed b)
```

Performs a division between two fixed-point numbers.

```C
Fixed fixmul(Fixed a, Fixed b)
```

Performs a multiplication between two fixed-point numbers.

```C
Fixed fixsin(Fixed angle)
```

Returns the sinus of a binary angle in fixed-point format.

```C
int fixtoi(Fixed f)
```

Turns a fixed-point number into an integer.

```C
void getBoundingBox(int x, int y, int w, int h, int cx, int cy, Fixed angle, Rect *out)
```

Calculates the bounds of the box that has the following properties :
- Has top-left corner at coordinates (x, y)
- Has width w and height h
- Rotates by a given angle around the point (cx, cy)
Writes the resulting box in "out". The resulting box is the smallest straight rectangle that contains all points of the input.

```C
int interpolatePathFixed(Fixed x[], Fixed y[], int t[], int nbPoints, Rect *out)
```

Given arrays of `nbPoints` X coordinates, Y coordinates and times, the function generates a curve that passes by the given points after the corresponding number of iterations. For every iteration, the calculated coordinates are written to `Rect *out`'s x and y components. The function returns 1 when the last point has been reached by the curve, and 0 otherwise. This version uses n2DLib's fixed point numbers, and thus is very fast but has limited accuracy.

```C
int interpolatePathFloat(float x[], float y[], int t[], int nbPoints, Rect *out)
```

Given arrays of `nbPoints` X coordinates, Y coordinates and times, the function generates a curve that passes by the given points after the corresponding number of iterations. For every iteration, the calculated coordinates are written to `Rect *out`'s x and y components. The function returns 1 when the last point has been reached by the curve, and 0 otherwise. This version uses floating-point numbers, and thus is much slower than `interpolatePathFixed` but has far better accuracy.

```C
Fixed itofix(int i)
```

Turns an integer into a fixed-point number.

```C
void rotate(int x, int y, int cx, int cy, Fixed angle, Rect* out)
```

Rotates the 2D point (x, y) around the 2D point (cx, cy) by the given angle, and stores the resulting point in "out" (w and h not modified).

```C
int sign(x)
```

Returns 1 if x is negative, 0 otherwise.

KEY DETECTION FUNCTIONS
=======================

```C
int get_key_pressed(t_key* report)
```

Detects if any key is being pressed ; if so, fills report with the corresponding data and returns 1. If no key is being pressed, fills report with _KEY_DUMMY and returns 0. NOTE : this doesn't detect the touchpad's arrow keys.

```C
int isKey(t_key k1, t_key k2)
```

Returns 1 if both keys match, or 0 if they don't. NOTE : this is very useful for example when comparing a key that has been filled with get_key_pressed() with an Ndless KEY_NSPIRE_ constant.

HARDWARE TIMERS
===============
The TI-Nspire calculators have 2 hardware timers that allows for accurate timing of any task. Each timer runs at 32 kHz. n2DLib provides a precise use for them, which is as follows :
- Every 0.000030517578125 second (roughly 30 µs, that is 32 768 times per second), each timer's value is decreased by 1.
- When a timer reaches 0, it stops decreasing until you reload a value in it.
To sum up, when a timer reads 0, it means the amount of time you passed has run out.

Everything here is by aeTIos and Streetwalrus from http://www.omnimaga.org/. Greetings to them !

```C
void timer_init(unsigned timer)
```

Initialises the first timer (unsigned timer = 0) or the second timer (unsigned timer = 1). Any other parameter than 0 or 1 will crash your calc badly. This MUST be called ONCE for every timer you use in your program or your timing will be invalid.

```C
void timer_restore(unsigned timer)
```

Restores the initial state of a timer. You MUST call this for every timer that you initialised via timer_init.

```C
void timer_load(unsigned timer, unsigned value)
```

Loads a value into a timer. This value will be decremented by the timer each tick until it reaches 0. Note that a timer will freeze until its value is non-zero.

```C
unsigned timer_read(unsigned timer)
```C

Reads a value from a timer. If it reads 0, it will always read as 0 until you load a new value into the timer.