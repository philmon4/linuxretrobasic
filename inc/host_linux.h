#ifndef HOST_LINUX_H_
#define HOST_LINUX_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include "vtxxx.h"

// mask arduino specific keywords in source
#define byte uint8_t
#define PROGMEM

#define SCREEN_WIDTH        21
#define SCREEN_HEIGHT       8

#define EXTERNAL_EEPROM         1
#define EXTERNAL_EEPROM_ADDR    0x50    // I2C address (7 bits)
#define EXTERNAL_EEPROM_SIZE    32768   // only <=32k tested (64k might work?)

#define MAGIC_AUTORUN_NUMBER    0xFC

#define EDBUFFER_LEN 256

// BASIC command line prompt
#define INPUT_PROMPT_STR ">"


extern char eline_buf[EDBUFFER_LEN];
extern int eline_preload;

void host_init(void);
void host_sleep(long ms);
void host_digitalWrite(int pin,int state);
int host_digitalRead(int pin);
int host_analogRead(int pin);
void host_pinMode(int pin, int mode);
void host_click();
void host_startupTone();
void host_cls();
void host_showBuffer();
void host_moveCursor(int x, int y);
void host_outputString(char *str);
void host_outputProgMemString(const char *str);
void host_outputChar(char c);
void host_outputFloat(float f);
char *host_floatToStr(float f, char *buf);
int host_outputInt(long val);
void host_newLine();

char *host_readLine();
char host_getKey();
char host_getchar();

bool host_ESCPressed();
void host_outputFreeMem(unsigned int val);
void host_saveProgram(bool autoexec);
void host_loadProgram();

#if EXTERNAL_EEPROM

#ifdef ARDUINO
  #include <I2cMaster.h>
#endif
void writeExtEEPROM(unsigned int address, byte data);
void host_directoryExtEEPROM();
bool host_saveExtEEPROM(char *fileName);
bool host_loadExtEEPROM(char *fileName);
bool host_removeExtEEPROM(char *fileName);
#endif


#endif /* HOST_LINUX_H */