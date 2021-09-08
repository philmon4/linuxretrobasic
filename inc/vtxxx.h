#ifndef VTXXX_H_
#define VTXXX_H_ 1.0

/**
 * @file vtxxx.h
 * @brief Subset of VT100 codes that worked with minicom and term on my linux machine. Very usefull for
 * highlighting messages from an embedded serial debug port.
 *
 * In debt to https://geoffg.net/Downloads/Terminal/VT100_User_Guide.pdf for his efforts,
 * and stack exchange when I couldn't figure out how to insert numbers into strings using c macros
 *
 * Usage example: char *vstr = "Hello "VT_BOLD"bold"VT_RESET;
 *
 * LICENSE
 * This code is released under the MIT Licence.
 * The only condition is: Keep this header comment at the top of the file containing this code.
 * Disclaimer: Any problems are your problems, and this code is not provided as fit for any purpose at all.
 * (C)2021 P.Mundy
 */
#define VTXXX_H_STR_HELPER(x) #x
#define VTXXX_H_STR(x) VTXXX_H_STR_HELPER(x)


/** @brief
 * VT100 terminal codes
 * usage:  VT_BOLD
 */
#define VT_ESC "\e"
#define VT_DISP "\e["

#define VT_RESET "\e[0m"
#define VT_BOLD "\e[1m"
#define VT_DIM "\e[2m"
#define VT_UNDERLINE "\e[4m"
#define VT_BLINK "\e[5m"
#define VT_REV "\e[7m"
#define VT_INVIS "\e[8m"

#define VT_BLACK_INK "\e[30m"
#define VT_RED_INK "\e[31m"
#define VT_GREEN_INK "\e[32m"
#define VT_YELLOW_INK "\e[33m"
#define VT_BLUE_INK "\e[34m"
#define VT_MAGENTA_INK "\e[35m"
#define VT_CYAN_INK "\e[36m"
#define VT_WHITE_INK "\e[37m"

#define VT_BLACK_PAPER "\e[40m"
#define VT_RED_PAPER "\e[41m"
#define VT_GREEN_PAPER "\e[42m"
#define VT_YELLOW_PAPER "\e[43m"
#define VT_BLUE_PAPER "\e[44m"
#define VT_MAGENTA_PAPER "\e[45m"
#define VT_CYAN_PAPER "\e[46m"
#define VT_WHITE_PAPER "\e[47m"

/**
 * @brief Save and restore terminal state
 */
#define VT_SAVE "\e7"
#define VT_RESTORE "\e8"

#define VT_CURSOR_UP_CMD "A"
#define VT_CURSOR_UP(A)  "\e[" VTXXX_H_STR(A) "A"

#define VT_CURSOR_DOWN_CMD "B"
#define VT_CURSOR_DOWN(A) "\e[" VTXXX_H_STR(A) "B"

#define VT_CURSOR_RIGHT_CMD "C"
#define VT_CURSOR_RIGHT(A)  "\e[" VTXXX_H_STR(A) "C"

#define VT_CURSOR_LEFT_CMD "D"
#define VT_CURSOR_LEFT(A)  "\e[" VTXXX_H_STR(A) "D"

#define VT_CURSOR_MOVETO_CMD  "H"
#define VT_CURSOR_MOVETO(L,C) "\e[" VTXXX_H_STR(L) ";" VTXXX_H_STR(C) "H"

#define VT_ERASE_TOEOL "\e[K"
#define VT_ERASE_FROMSOL "\e[1K"
#define VT_ERASE_LINE "\e[2K"

#define VT_ERASE_ENDSCREEN "\e[0J"
#define VT_ERASE_STARTSCREEN "\e[1J"
#define VT_ERASE_SCREEN "\e[2J"


void vt_cursor_moveto( char *p_vtcmd, int x, int y);
void vt_cursor_up( char *p_vtcmd, int n);
void vt_cursor_down( char *p_vtcmd, int n);
void vt_cursor_left( char *p_vtcmd, int n);
void vt_cursor_right( char *p_vtcmd, int n);


#endif /*VTXXX_H_*/
