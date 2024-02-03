#ifndef MY_BIG_CHAR_H
#define MY_BIG_CHAR_H

#include <stdint.h>
#include "myterm.h"

// --- Alternate mode special characters ---

#define ALT_BOX_CH 'a' // Alt chat mode colored box character
#define ALT_TLC_CH 'l' // Alt chat mode top-left corner character
#define ALT_TRC_CH 'k' // Alt chat mode top-right corner character
#define ALT_BLC_CH 'm' // Alt chat mode bottom-left corner character
#define ALT_BRC_CH 'j' // Alt chat mode bottom-right corner character
#define ALT_HOL_CH 'q' // Alt chat mode horizontal line character
#define ALT_VEL_CH 'x' // Alt chat mode vertical line character

// !-- Alternate mode special characters --!

// BigChar is a 8x8 bitmap
// representing a characted drawing
typedef int64_t BigChar;

// Prints string with alt charset
int bc_printA(char *str);

// Prints pseudo-graphical border-box with top-left
// corner at (x1,y1) and given width and height
int bc_box(int x1, int y1, int width, int height);

// Prints given 8x8 bigchar at (x,y) with given foreground and background colors
int bc_printbigchar(BigChar ch, int x, int y, MTColor fg_color, MTColor bg_color);

// Sets a bit at (x,y) to value of 0 or 1
int bc_setbigcharpos (BigChar *ch, int x, int y, int value);

// Retrieves a bit from given BigChar from (x,y) position
int bc_getbigcharpos (BigChar ch, int x, int y, int *value);

// Prints given amount of BigChars to file
int bc_bigcharwrite (int fd, BigChar *chrs, int count);

// Reads given amount of big chars to dst and sets the number of chars read
int bc_bigcharread (int fd, BigChar *dst, int amount, int *chrs_read);

// Returns digit's BigChar counterpart.
// Return -1 if given smth aside from digit
BigChar digitToBigChar(char digit);

#define BC_ZERO 0b\
11111111\
11000011\
11000011\
11000011\
11000011\
11000011\
11000011\
11111111

#define BC_ONE 0b\
00011100\
00111100\
00001100\
00001100\
00001100\
00001100\
00001100\
01111111

#define BC_TWO 0b\
11111111\
11000011\
00000011\
11111111\
11111111\
11000000\
11000011\
11111111

#define BC_THREE 0b\
11111111\
11000011\
00000011\
00111111\
00000011\
00000011\
11000011\
11111111

#define BC_FOUR 0b\
11000011\
11000011\
11000011\
11111111\
00000011\
00000011\
00000011\
00000011

#define BC_FIVE 0b\
11111111\
11000000\
11000000\
11111111\
00000011\
00000011\
00000011\
11111111

#define BC_SIX 0b\
11111111\
11000011\
11000000\
11111111\
11000011\
11000011\
11000011\
11111111

#define BC_SEVEN 0b\
11111111\
11000011\
00000110\
00001100\
00011000\
00110000\
01100000\
11000000

#define BC_EIGHT 0b\
11111111\
11000011\
11000011\
11111111\
11000011\
11000011\
11000011\
11111111

#define BC_NINE 0b\
11111111\
11000011\
11000011\
11111111\
00000011\
00000011\
00000011\
11111111

#endif // MY_BIG_CHAR