#ifndef __Motor
#define __Motor

#include <iostream>
#include "UartComs.h"

class Motor
{
private:
	UartComs &m_uc;

    char m_startByte;
    
public:
    Motor(const char startByte, UartComs &uc);
    bool setRPM(const uint8_t RPM);
};

#endif
