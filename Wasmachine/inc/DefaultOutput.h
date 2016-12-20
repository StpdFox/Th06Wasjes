#ifndef __DefaultOutPut
#define __DefaultOutPut

class DefaultOutput
{
private:
    char m_startByte;
    char m_onByte;
    char m_offByte;
    
public:
    DefaultOutput(const char startByte, const char onByte, const char offByte);
    void on() const;
    void off() const;
}

#endif