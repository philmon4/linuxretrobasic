

#include <string.h>
#include "vtxxx.h"
#include "numeric.h"

/**
 * @brief Runtime calculated cursor movement escape sequence.
 * NB. you might want to use the MACRO version for immediate values fixed at compile time:
 *  ie. VT_CURSOR_MOVETO(1,1)
 * @param char *p_vtcmd : pointer to buffer big enough to append escape sequence
 * @param int n : number of character positions to move.
*/
void vt_cursor_moveto( char *p_vtcmd, int x, int y){
    int ix = 0;
    int l = 0;

    strcpy(p_vtcmd, VT_DISP); // preamble
    ix = strlen(VT_DISP);

    l = int_to_sz(p_vtcmd+ix, y);  /* fixed bug y goes first (vert parameter) */
    ix += l;

    strcat(p_vtcmd+ix, ";");
    ix++;

    l = int_to_sz(p_vtcmd+ix, x);
    ix += l;

    strcpy(p_vtcmd+ix, VT_CURSOR_MOVETO_CMD);
}

/**
 * @brief Runtime calculated cursor movement escape sequence.
 * NB. you might want to use the MACRO version for immediate values fixed at compile time:
 *  ie. VT_CURSOR_UP(1)
 * @param char *p_vtcmd : pointer to buffer big enough to append escape sequence
 * @param int n : number of character positions to move.
*/
void vt_cursor_up( char *p_vtcmd, int n){
    int ix = 0;
    int l = 0;

    strcpy(p_vtcmd, VT_DISP); // preamble
    ix = strlen(VT_DISP);

    l = int_to_sz(p_vtcmd+ix, n);
    ix += l;

    strcpy(p_vtcmd+ix, VT_CURSOR_UP_CMD);
}


/**
 * @brief Runtime calculated cursor movement escape sequence.
 * NB. you might want to use the MACRO version for immediate values fixed at compile time:
 *  ie. VT_CURSOR_UP(1)
 * @param char *p_vtcmd : pointer to buffer big enough to append escape sequence
 * @param int n : number of character positions to move.
*/
void vt_cursor_down( char *p_vtcmd, int n){
    int ix = 0;
    int l = 0;

    strcpy(p_vtcmd, VT_DISP); // preamble
    ix = strlen(VT_DISP);

    l = int_to_sz(p_vtcmd+ix, n);
    ix += l;

    strcpy(p_vtcmd+ix, VT_CURSOR_DOWN_CMD);
}


/**
 * @brief Runtime calculated cursor movement escape sequence.
 * NB. you might want to use the MACRO version for immediate values fixed at compile time:
 *  ie. VT_CURSOR_UP(1)
 * @param char *p_vtcmd : pointer to buffer big enough to append escape sequence
 * @param int n : number of character positions to move.
*/
void vt_cursor_left( char *p_vtcmd, int n){
    int ix = 0;
    int l = 0;

    strcpy(p_vtcmd, VT_DISP); // preamble
    ix = strlen(VT_DISP);

    l = int_to_sz(p_vtcmd+ix, n);
    ix += l;

    strcpy(p_vtcmd+ix, VT_CURSOR_LEFT_CMD);
}


/**
 * @brief Runtime calculated cursor movement escape sequence.
 * NB. you might want to use the MACRO version for immediate values fixed at compile time:
 *  ie. VT_CURSOR_UP(1)
 * @param char *p_vtcmd : pointer to buffer big enough to append escape sequence
 * @param int n : number of character positions to move.
*/
void vt_cursor_right( char *p_vtcmd, int n){
    int ix = 0;
    int l = 0;

    strcpy(p_vtcmd, VT_DISP); // preamble
    ix = strlen(VT_DISP);

    l = int_to_sz(p_vtcmd+ix, n);
    ix += l;

    strcpy(p_vtcmd+ix, VT_CURSOR_RIGHT_CMD);
}








