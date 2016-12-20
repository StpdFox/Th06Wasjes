#include "TempSensor.h"
#include <stdlib> //ToDo remove when rand() is removed

TempSensor::TempSensor(const char reqByte) : m_reqByte(reqByte) 
{}

void TempSensor::readTemp()
{
    //ToDo put here the sensor read code
    m_temp = rand() % 100;
}

void TempSensor::updateState()
{
    readTemp();
    m_listener->updateTemp(this);
}

void TempSensor::setListener(const TempListener *l)
{
    m_listener = l;
}

uint TempSensor::getTemp() const
{
    return m_temp;
}