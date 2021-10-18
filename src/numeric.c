/**

MIT License
No warranty, or intention that it's fit for any purpose.
Use where you want, as long as this comment and license are
placed in the files containing this source code.

(C)Phil Mundy 2021-09-01

*/

#include <stdlib.h>
#include <string.h>
#include <math.h>


/* series generator coefficients */
static const double c[6]={
    1.276278962f,
    -.142630785f,
    0.004559008f,
    -.000068294f,
    0.000000592f,
    -.000000003f,
};



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



/**
 * @brief
 * Core sine and cosine generator
 * @params
 * r = angle in radians
 * cosine_select=1 for cosine(r), 0 for sine(r)
 * @description
 * algorithm extracted from zx spectrum basic rom
 * works nicely with doubles, only used floats to fit
 * original application.
 * Thanks go out to:
 * https://albertveli.wordpress.com/2015/01/10/zx-sine/
 * https://namoseley.wordpress.com/2012/09/26/arduinoavr-and-zx-spectrum-sin-routines/
 */
float sin_cos( float r, int cosine_select){
        double y, w,z,p;
        /* scale for radians input and modulo range of input value to +/- 0.5 swings */
        y=r/(2*M_PI)+(cosine_select?0.25:0); /* add on 90deg shift for cosine if selected */
        /* if you change the rounding function check it gives right results for positive
         * and negative values at the wrap-around points!
         * Some rounding methods won't work how you expect.
         */
        y=y-round(y);
        w = 4*y;
        /* algorithm is quite poor as it approches +/-0.5 so make use of symmetry to limit range to +/-0.25*/
        if (w>1)
            w=2-w;
        if (w<-1)
            w=-2-w;
        z = 2*w*w-1;
        p = c[0] + 2*c[1]*z + 2*c[2]*(2*z*z-1) + 2*c[3]*(4*z*z*z-3*z) + 2*c[4]*(8*z*z*z*z - 8*z*z + 1) + 2*c[5]*(16*z*z*z*z*z - 20*z*z*z + 5*z ) ;
        return (float)(w*p);
}


