#include "myterm.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

// --- Terminal ASCII Escape Sequences ---

#define CLEAR_SCREEN_SEQ "\E[H\E[2J"
#define CURSOR_UP        "\E[%dA"
#define CURSOR_DOWN      "\E[%dB"
#define CURSOR_LEFT      "\E[%dD"
#define CURSOR_RIGHT     "\E[%dC"
#define CURSOR_POS       "\E[%d;%dH"

#define OCTAL_COLOR "\E[%dm"
#define FG_OCT_BASE 30
#define BG_OCT_BASE 40     

// !-- Terminal ASCII Escape Sequences --!

#define LEFT

// Clears the screen and moves the cursor 
// into the top-left corner
int mt_clrscr(void) {
    printf(CLEAR_SCREEN_SEQ);
    return 0;
};

// Moves cursor to a given position.
int mt_gotoXY(int line, int col) {
    printf(CURSOR_POS, line, col);
    return 0;
}

// Retrieves terminal size
int mt_getscreensize(int *rows, int *cols) {
    struct winsize w;
    if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) {
        *rows = w.ws_row;
        *cols = w.ws_col;
        return 0;
    }

    return -1;
}

// Sets the font color for the next printed characters
int mt_setfgcolor(MTColor color) {
    printf(OCTAL_COLOR, FG_OCT_BASE + color);
    return 0;
}

// Sets the background color for the next printed characters
int mt_setbgcolor(MTColor color) {
    printf(OCTAL_COLOR, BG_OCT_BASE + color);
    return 0;
}
