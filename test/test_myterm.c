#include "../myterm.h"
#include <stdio.h>
#include <math.h>

int main() {
    mt_clrscr();

    int rows, cols;
    if (mt_getscreensize(&rows, &cols) == -1) {
        printf("getting screen size failed");
        return -1;
    }

    int x = floor(rows/2), y = floor(cols/2);

    mt_gotoXY(x,y);
    mt_setbgcolor(MTWHITE);
    mt_setfgcolor(MTBLACK);    
    printf("Hello from center of the screen!");

    mt_gotoXY(1,1);
    mt_setbgcolor(MTRED);
    mt_setfgcolor(MTYELLOW);
    printf("Hello from top-left corner of the screen!");

    return 0;
}