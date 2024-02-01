#ifndef MY_TERM_H
#define MY_TERM_H

typedef enum MTColor {
    MTWHITE
} MTColor;

// Clears the screen and moves the cursor 
// into the top-left corner
int mt_clrscr(void);

// Moves cursor to a given position.
int mt_gotoXY(int line, int col);

// Retrieves terminal size
int mt_getscreensize(int *rows, int *cols);

// Sets the font color for the next printed characters
int mt_setfgcolor(MTColor);

// Sets the background color for the next printed characters
int mt_setbgcolor(MTColor);

#endif // MY_TERM_H