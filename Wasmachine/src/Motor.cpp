#include <iostream>

#include "Motor.h"

Motor::Motor(const char startByte, UartComs &uc) :
	m_uc(uc),
	m_startByte(startByte)
{}

bool Motor::setRPM(const uint8_t RPM)
{
	if(m_uc.writeUart(m_startByte, RPM) == -1) return false;

	return true;
}
