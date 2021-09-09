


// Test compile: gcc  -I inc -D LINUX src/main.c src/host_linux.c src/basic.c -lreadline -lm

#include "config.h"
#include "basic.h"
#include "host.h"




unsigned char mem[MEMORY_SIZE];

unsigned char tokenBuf[TOKEN_BUF_SIZE];

const char welcomeStr[] PROGMEM = "Arduino BASIC";


int main( int argc, char* argv[]){

    reset();
    host_init();
    host_cls();



    while(1){
        int ret = ERROR_NONE;
        char *input = host_readLine();
        // special editor commands
        if (input[0] == '?' && input[1] == 0) {
            host_outputFreeMem(sysVARSTART - sysPROGEND);
        }
        // otherwise tokenize
        ret = tokenize((unsigned char*)input, tokenBuf, TOKEN_BUF_SIZE);

           // execute the token buffer
        if (ret == ERROR_NONE) {
            host_newLine();
            ret = processInput(tokenBuf);
        }
        if (ret != ERROR_NONE) {
            host_newLine();
            if (lineNumber !=0) {
                host_outputInt(lineNumber);
                host_outputChar('-');
            }
            #ifdef ARDUINO
                host_outputProgMemString((char *)pgm_read_word(&(errorTable[ret])));
            #else
                host_outputProgMemString((char *)errorTable[ret]);
            #endif
        }
    }

    return 0;
}