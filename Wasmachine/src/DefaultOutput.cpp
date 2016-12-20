#include "DefaultOutput.h"

DefaultOutput::DefaultOutput(const char startByte, const char onByte, const char offByte) :
    m_startByte(startByte),
    m_onByte(onByte),
    m_offByte(offByte)
{}

DefaultOutput::on() const
{
    //Send on message
}

DefaultOutput::off() const
{
    //Send off message
}