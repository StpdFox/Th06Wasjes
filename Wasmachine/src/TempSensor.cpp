#include "TempSensor.h"
#include <stdlib.h> //ToDo remove when rand() is removed

TempSensor::TempSensor(const char reqByte) :
	m_reqByte(reqByte),
	m_listener(nullptr)
{}

void TempSensor::readTemp()
{
    //ToDo put here the sensor read code
    //m_temp = rand() % 100;
    ++m_temp;
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
