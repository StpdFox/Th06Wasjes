#include "WaterLevelSensor.h"
#include <stdlib> //ToDo remove when rand() is removed

WaterLevelSensor::WaterLevelSensor(const char reqByte) : m_requestByte(reqByte)
{}

void WaterLevelSensor::readWaterLevel()
{
    //ToDo put here the sensor read code
    m_waterLevel = rand() % 15;
}

void WaterLevelSensor::updateState()
{
    readWaterLevel();
    m_m_wlvlListeners->updateWLevel(this);
}

void WaterLevelSensor::setListener(const WaterLvlListener *w)
{
    m_wlvlListeners = w;
}

uint WaterLevelSensor::getWaterLevel() const
{
    return m_waterLevel;
}