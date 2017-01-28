#ifndef __DefaultOutPut
#define __DefaultOutPut

#include "UartComs.h"

class DefaultOutput
{
private:
	UartComs &m_uc;

	uint8_t m_startByte;
	uint8_t m_onByte;
	uint8_t m_offByte;
    
public:
    DefaultOutput(const uint8_t startByte, const uint8_t onByte, const uint8_t offByte, UartComs &m_uc);
    bool on() const;
    bool off() const;
};

#endif
