#include <iostream>

#include "DefaultOutput.h"

DefaultOutput::DefaultOutput(const char startByte, const char onByte, const char offByte) :
    m_startByte(startByte),
    m_onByte(onByte),
    m_offByte(offByte)
{}

void DefaultOutput::on() const
{
    std::cout << "On" << std::endl;
}

void DefaultOutput::off() const
{
    std::cout << "Off" << std::endl;
}