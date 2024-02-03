#include "../mybigchar.h"
#include "../myterm.h"
#include <stdio.h>

int main() {
    mt_clrscr();
    bc_box(2, 2, 82, 10);

    for (int i = 0; i < 10; i++) {
        getchar();
        int j = i % 7;
        bc_printbigchar(digitToBigChar(i), 3, 3+i*(sizeof(BigChar)), j, (!j) ? MTWHITE : MTBLACK);
    }

    mt_gotoXY(13, 1);
    getchar();
    return 0;
}