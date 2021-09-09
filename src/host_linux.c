/**
 * @file host_linux.c
 * @brief Linux version of original Arduino host.c code, using linux IO.
 *
 * Trying to keep the api unchanged to minimise impact on the core basic.c.
 *
 * As BASIC uses a line based entry, C readline() a perfect fit.
 * Code avoids use of printf,sprintf,scanf etc. because they are heavyweights
 * and I want as much code as possible to be easily ported to microcontrollers.
 *
 * This is based on code released at: Github:robinhedwards/ArduinoBASIC
 *
 * test compile: gcc -c -I inc -D LINUX src/host_linux.c -lreadline
 *
 * LICENSE
 * This code is released under the MIT Licence.
 * The only condition is: Keep this header comment at the top of the file containing this code.
 * Disclaimer: Any problems are your problems, and this code is not provided as fit for any purpose at all.
 * (C)2021 P.Mundy
 */


#include "host.h"
#include <stdlib.h>
#include "numeric.h"
#include "vtxxx.h"

#ifdef LINUX
 #include "crossline.h"
#endif

const char bytesFreeStr[] PROGMEM = "bytes free";

char eline_buf[EDBUFFER_LEN];
int eline_preload = 0; /*flag when eline has contents preloaded to edit a line */

void host_init(void) {
    //#[STUB
}

void host_sleep(long ms) {
    //#[STUB
    //delay(ms);
}

void host_digitalWrite(int pin,int state) {
    //#[STUB
    //digitalWrite(pin, state ? HIGH : LOW);
}

int host_digitalRead(int pin) {
    //#[STUB
    //return digitalRead(pin);
    return -1;
}

int host_analogRead(int pin) {
    //#[STUB
    //return analogRead(pin);
    return -1;
}

void host_pinMode(int pin,int mode) {
    //#[STUB
    //pinMode(pin, mode);
}

/* Keyboard click */
void host_click() {
    //#[STUB
}

/* Beep on power up */
void host_startupTone() {   
    //#[STUB
}

void host_cls() {
    puts(VT_ERASE_SCREEN);
}

void host_moveCursor(int x, int y) {
    char p_vtcmd[16];

    vt_cursor_moveto(p_vtcmd, x, y);
    host_outputString(p_vtcmd);
}

void host_showBuffer() {
    //#[STUB
}

void scrollBuffer() {
    //#[STUB
}

void host_outputString(char *str) {
    int c;
    while( (c=*str++)!='\0')
        host_outputChar(c);
}

void host_outputProgMemString(const char *p) {
    host_outputString((char *)p);
}

void host_outputChar(char c) {
    putchar(c);
}

int host_outputInt(long num) {
    // returns len
    long i = num, xx = 1;
    int c = 0;
    do {
        c++;
        xx *= 10;
        i /= 10;
    } 
    while (i);

    for (int i=0; i<c; i++) {
        xx /= 10;
        char digit = ((num/xx) % 10) + '0';
        host_outputChar(digit);
    }
    return c;
}



void host_outputFloat(float f) {
    char buf[16];
    host_outputString(float_to_sz(f, buf));
}

void host_newLine() {
    host_outputChar('\r');
    host_outputChar('\n');
}



/**
readline using linux std readline()  fn.
the downside is, the linux call doesn't allow pre-stuffing
a string into the buffer which would have been handy to
edit an existing BASIC line
*/
char *host_readLine() {
    char *line;
    

    // line = readline(INPUT_PROMPT_STR);

    /* preserve buffer contents if preloaded to edit existing line */
    if ( eline_preload ){
        eline_preload = 0;
    }
    else {
        eline_buf[0]='\0';
    }
    line = crossline_readline2("#", eline_buf, EDBUFFER_LEN);

    return line;
}

char host_getKey() {
    //#[STUB
    /*
    char c = inkeyChar;
    inkeyChar = 0;
    if (c >= 32 && c <= 126)
        return c;
    else return 0;
    */
    return 0;
}

char host_getchar() {

    char c = crossline_getch(); // gets a char with no echo

    return c;
}


bool host_ESCPressed() {
    //[#STUB
    /*
    while (keyboard.available()) {
        // read the next key
        inkeyChar = keyboard.read();
        if (inkeyChar == PS2_ESC)
            return true;
    }
    return false;
    */
    return false;
}

void host_outputFreeMem(unsigned int val)
{
    host_newLine();
    host_outputInt(val);
    host_outputChar(' ');
    host_outputProgMemString(bytesFreeStr);      
}

void host_saveProgram(bool autoexec) {
    //[#STUB
/*
    EEPROM.write(0, autoexec ? MAGIC_AUTORUN_NUMBER : 0x00);
    EEPROM.write(1, sysPROGEND & 0xFF);
    EEPROM.write(2, (sysPROGEND >> 8) & 0xFF);
    for (int i=0; i<sysPROGEND; i++)
        EEPROM.write(3+i, mem[i]);
*/
}

void host_loadProgram() {
    //[#STUB
/*
    // skip the autorun byte
    sysPROGEND = EEPROM.read(1) | (EEPROM.read(2) << 8);
    for (int i=0; i<sysPROGEND; i++)
        mem[i] = EEPROM.read(i+3);
*/
}


#if EXTERNAL_EEPROM
/*
#include <I2cMaster.h>
extern TwiMaster rtc;
*/

void writeExtEEPROM(unsigned int address, byte data) 
{
    /*
  if (address % 32 == 0) host_click();
  rtc.start((EXTERNAL_EEPROM_ADDR<<1)|I2C_WRITE);
  rtc.write((int)(address >> 8));   // MSB
  rtc.write((int)(address & 0xFF)); // LSB
  rtc.write(data);
  rtc.stop();
  delay(5);
  */
}
 
byte readExtEEPROM(unsigned int address) 
{
    /*
  rtc.start((EXTERNAL_EEPROM_ADDR<<1)|I2C_WRITE);
  rtc.write((int)(address >> 8));   // MSB
  rtc.write((int)(address & 0xFF)); // LSB
  rtc.restart((EXTERNAL_EEPROM_ADDR<<1)|I2C_READ);
  byte b = rtc.read(true);
  rtc.stop();
  return b;
  */
  return 0;
}

// get the EEPROM address of a file, or the end if fileName is null
unsigned int getExtEEPROMAddr(char *fileName) {
    /*
    unsigned int addr = 0;
    while (1) {
        unsigned int len = readExtEEPROM(addr) | (readExtEEPROM(addr+1) << 8);
        if (len == 0) break;
        
        if (fileName) {
            bool found = true;
            for (int i=0; i<=strlen(fileName); i++) {
                if (fileName[i] != readExtEEPROM(addr+2+i)) {
                    found = false;
                    break;
                }
            }
            if (found) return addr;
        }
        addr += len;
    }
    return fileName ? EXTERNAL_EEPROM_SIZE : addr;
    */
    return 0;
}

void host_directoryExtEEPROM() {
    /*
    unsigned int addr = 0;
    while (1) {
        unsigned int len = readExtEEPROM(addr) | (readExtEEPROM(addr+1) << 8);
        if (len == 0) break;
        int i = 0;
        while (1) {
            char ch = readExtEEPROM(addr+2+i);
            if (!ch) break;
            host_outputChar(readExtEEPROM(addr+2+i));
            i++;
        }
        addr += len;
        host_outputChar(' ');
    }
    host_outputFreeMem(EXTERNAL_EEPROM_SIZE - addr - 2);
    */
}

bool host_removeExtEEPROM(char *fileName) {
    /*
    unsigned int addr = getExtEEPROMAddr(fileName);
    if (addr == EXTERNAL_EEPROM_SIZE) return false;
    unsigned int len = readExtEEPROM(addr) | (readExtEEPROM(addr+1) << 8);
    unsigned int last = getExtEEPROMAddr(NULL);
    unsigned int count = 2 + last - (addr + len);
    while (count--) {
        byte b = readExtEEPROM(addr+len);
        writeExtEEPROM(addr, b);
        addr++;
    }
    return true;
    */
    return 0;
}

bool host_loadExtEEPROM(char *fileName) {
    /*
    unsigned int addr = getExtEEPROMAddr(fileName);
    if (addr == EXTERNAL_EEPROM_SIZE) return false;
    // skip filename
    addr += 2;
    while (readExtEEPROM(addr++)) ;
    sysPROGEND = readExtEEPROM(addr) | (readExtEEPROM(addr+1) << 8);
    for (int i=0; i<sysPROGEND; i++)
        mem[i] = readExtEEPROM(addr+2+i);
        */
        return false;
}

bool host_saveExtEEPROM(char *fileName) {
    /*
    unsigned int addr = getExtEEPROMAddr(fileName);
    if (addr != EXTERNAL_EEPROM_SIZE)
        host_removeExtEEPROM(fileName);
    addr = getExtEEPROMAddr(NULL);
    unsigned int fileNameLen = strlen(fileName);
    unsigned int len = 2 + fileNameLen + 1 + 2 + sysPROGEND;
    if ((long)EXTERNAL_EEPROM_SIZE - addr - len - 2 < 0)
        return false;
    // write overall length
    writeExtEEPROM(addr++, len & 0xFF);
    writeExtEEPROM(addr++, (len >> 8) & 0xFF);
    // write filename
    for (int i=0; i<strlen(fileName); i++)
        writeExtEEPROM(addr++, fileName[i]);
    writeExtEEPROM(addr++, 0);
    // write length & program    
    writeExtEEPROM(addr++, sysPROGEND & 0xFF);
    writeExtEEPROM(addr++, (sysPROGEND >> 8) & 0xFF);
    for (int i=0; i<sysPROGEND; i++)
        writeExtEEPROM(addr++, mem[i]);
    // 0 length marks end
    writeExtEEPROM(addr++, 0);
    writeExtEEPROM(addr++, 0);
    return true;
    */
    return false;
}

#endif /* EXTERNAL_EEPROM */


