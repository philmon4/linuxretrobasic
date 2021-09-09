/**

MIT License
No warranty, or intention that it's fit for any purpose.
Use where you want, as long as this header and license are
placed in the files containing this source code.

(C)Phil Mundy 2021-09-01

*/

#include <stdlib.h>
#include <string.h>


int float_to_sz(char *buf, float f) {
    int len=0;
    //sprintf(buf,"%f",f);
    gcvt(f,6,buf);
    len = strlen(buf);
    return len;
}


/**
 assumes 4 byte int

 stores stringised int in buf provided, and returns the number of chars used.
 */
int int_to_sz( char *buf, int val){
    char ns[12];

    int digit;
    int divisor = 1000000000;
    int leading_zero=1;
    int place = 0;

    if (val<0){
        val=-val;
        *(buf) = '-';
        place++;
    }
    if (val==0){
        *buf = '0';
        place++;
    }
    else{
        do{
            digit=val/divisor;
            if ((digit!=0)||(!leading_zero))
            {
                leading_zero=0;
                val = val-digit*divisor;
                *(buf+place) = '0'+digit;
                place++;
            }
            divisor=divisor/10;
        }while (divisor>0);
    }
    /* terminate sz */
    *(buf+place) = '\0';

    return place;
}