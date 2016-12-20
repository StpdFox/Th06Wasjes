#ifndef __Motor
#define __Motor

class Motor
{
private:
    char m_startByte;
    
public:
    Motor(const char startByte);
    setRPM(const uint RPM);
}

#endif