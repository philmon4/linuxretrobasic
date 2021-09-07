

#include <string.h>
#include "vtxxx.h"
#include "numeric.h"


void vt_cursor_moveto( char *p_vtcmd, int x, int y){
    int ix = 0;
    int l = 0;

    strcpy(p_vtcmd, VT_DISP); // preamble
    ix = strlen(VT_DISP);

    l = int_to_sz(p_vtcmd+ix, x);
    ix += l;

    strcat(p_vtcmd+ix, ";");
    ix++;

    l = int_to_sz(p_vtcmd+ix, y);
    ix += l;

    strcat(p_vtcmd+ix, VT_CURSOR_MOVETO_CMD);
}

/**
runtime calculated cursor movement
use the MACRO version for immediate values
*/
void vt_cursor_up( char *p_vtcmd, int n){
    int ix = 0;
    int l = 0;

    strcpy(p_vtcmd, VT_DISP); // preamble
    ix = strlen(VT_DISP);

    l = int_to_sz(p_vtcmd+ix, n);
    ix += l;

    strcat(p_vtcmd+ix, VT_CURSOR_UP_CMD);
}


