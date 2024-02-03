#include "mybigchar.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Array of Big Chars for digits
BigChar bc_digits[10] = {
    BC_ZERO,
    BC_ONE,
    BC_TWO,
    BC_THREE,
    BC_FOUR,
    BC_FIVE,
    BC_SIX,
    BC_SEVEN,
    BC_EIGHT,
    BC_NINE,
};

// Prints string with alt charset
int bc_printA(char *str) {
    printf("\E(0%s\E(B", str);
    return 0;
}

// Prints pseudo-graphical border-box with top-left
// corner at (x1,y1) and given width and height
int bc_box(int x1, int y1, int width, int height) {
    if (width < 1 || height < 1) return -1;

    char *hline = (char*)malloc(width + 1);
    char *row = (char*)malloc(width + 1);

    memset(hline+1, 'q', width-1);
    memset(row+1, ' ', width-1);
    hline[0]       = ALT_TLC_CH; // top-left corner
    hline[width-1] = ALT_TRC_CH; // top-right corner
    hline[width]   = '\0';
    row[0]         = 'x';
    row[width-1]   = 'x';
    row[width]     = '\0';

    mt_gotoXY(y1, x1);
    bc_printA(hline);
    for (int i = 1; i <= height-1; i++) {
        mt_gotoXY(y1+i, x1);
        bc_printA(row);
    }


    hline[0]       = ALT_BLC_CH; // bottom-left corner
    hline[width-1] = ALT_BRC_CH; // bottom-right corner
    mt_gotoXY(y1+height-1, x1);
    bc_printA(hline);

    free(hline);
    free(row);

    return 0;
}

// Prints given 8x8 bigchar at (x,y) with given foreground and background colors
int bc_printbigchar(BigChar ch, int x, int y, MTColor fg_color, MTColor bg_color) {
    #define BIG_CHAR_BUFFER_SIZE 10 // 8 symbols for a row + LF + null terminator
    char buf[BIG_CHAR_BUFFER_SIZE];
    char shift = 63;

    mt_setbgcolor(bg_color);
    mt_setfgcolor(fg_color);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char bit = (ch >> shift--) & 1;
            buf[j] = (bit) ? ALT_BOX_CH : ' ';
        }
        buf[BIG_CHAR_BUFFER_SIZE-2] = "\n";

        mt_gotoXY(x+i,y);
        bc_printA(buf);
    }

    mt_setbgcolor(MTDEFAULT);
    mt_setfgcolor(MTDEFAULT);
    return 0;
}

// Sets a bit at (x,y) to value of 0 or 1
int bc_setbigcharpos (BigChar *ch, int x, int y, int value) {
    if (x < 0 || 7 < x || y < 0 || 7 < y)
        return -1;
    if (value < 0 || 1 < value)
        return -1;

    int mask = 1 << (63 - (x * y + x));
    *ch = (value) ? *ch | mask : *ch & ~mask;

    return 0;
}

// Retrieves a bit from given BigChar from (x,y) position
int bc_getbigcharpos (BigChar ch, int x, int y, int *value) {
    if (x < 0 || 7 < x || y < 0 || 7 < y)
        return -1;

    *value = (ch >> 63 - (x * y + x)) & 1;
    return 0;
}

// Prints given amount of BigChars to file
int bc_bigcharwrite (int fd, BigChar *chrs, int count) {
    return write(fd, chrs, sizeof(BigChar) * count);
}

// Reads given amount of big chars to dst and sets the number of chars read
int bc_bigcharread (int fd, BigChar *dst, int amount, int *chrs_read) {
    int bytes_read = read(fd, dst, amount * sizeof(BigChar));
    if (bytes_read == -1) return -1;

    *chrs_read = bytes_read / sizeof(BigChar);
    return 0;
}

BigChar digitToBigChar(char digit) {
    switch (digit) {
        case 0: return BC_ZERO;
        case 1: return BC_ONE;
        case 2: return BC_TWO;
        case 3: return BC_THREE; 
        case 4: return BC_FOUR; 
        case 5: return BC_FIVE;
        case 6: return BC_SIX;
        case 7: return BC_SEVEN;
        case 8: return BC_EIGHT;
        case 9: return BC_NINE;
        default: return -1;
    }
}