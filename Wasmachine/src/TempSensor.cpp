#include "TempSensor.h"

TempSensor::TempSensor(const char reqByte, UartComs &uc) :
	m_uc(uc),
	m_reqByte(reqByte),
	m_listener(nullptr)
{}

void TempSensor::readTemp()
{
	m_temp = m_uc.readUart(8);
}

void TempSensor::updateState()
{
    readTemp();
    m_listener->updateTemp(this);
}

void TempSensor::setListener(TempListener *l)
{
    m_listener = l;
}

uint TempSensor::getTemp() const
{
    return m_temp;
}


TempSensor::~TempSensor()
{}
