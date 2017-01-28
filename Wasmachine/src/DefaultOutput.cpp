#include <iostream>

#include "DefaultOutput.h"

DefaultOutput::DefaultOutput(const uint8_t startByte, const uint8_t onByte, const uint8_t offByte, UartComs &uc) :
	m_uc(uc),
    m_startByte(startByte),
    m_onByte(onByte),
    m_offByte(offByte)
{}

bool DefaultOutput::on() const
{
    if(m_uc.writeUart(m_startByte, m_onByte) == -1) return false;

    return true;
}

bool DefaultOutput::off() const
{
    if(m_uc.writeUart(m_startByte, m_offByte) == -1) return false;

    return true;
}
