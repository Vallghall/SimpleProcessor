#include "myterm.h"
#include <stdio.h>

// Clears the screen and moves the cursor 
// into the top-left corner
int mt_clrscr(void) {
    printf("\E[H\E");
};

// Moves cursor to a given position.
int mt_gotoXY(int line, int col);

// Retrieves terminal size
int mt_getscreensize(int *rows, int *cols);

// Sets the font color for the next printed characters
int mt_setfgcolor(MTColor);

// Sets the background color for the next printed characters
int mt_setbgcolor(MTColor);