#ifndef __Motor
#define __Motor

#include <sys/types.h>

class Motor
{
private:
    char m_startByte;
    
public:
    Motor(const char startByte);
    void setRPM(const uint RPM);
};

#endif