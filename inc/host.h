#ifndef HOST_H_
#define HOST_H_ 1.0

#ifdef LINUX
 #include "host_linux.h"
#endif

#ifdef ARDUINO
 #include "host_arduino.h"
#endif

#endif /* HOST_H_ */