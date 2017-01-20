#include "WaterLevelSensor.h"
#include <stdlib.h> //ToDo remove when rand() is removed

WaterLevelSensor::WaterLevelSensor(const char reqByte) :
	m_requestByte(reqByte),
	m_wlvlListeners(nullptr)
{}

void WaterLevelSensor::readWaterLevel()
{
    //ToDo put here the sensor read code
    //m_waterLevel = rand() % 15;
    ++m_waterLevel;
}

void WaterLevelSensor::updateState()
{
    readWaterLevel();
    m_wlvlListeners->updateWLevel(this);
}

void WaterLevelSensor::setListener(WaterLvlListener *w)
{
    m_wlvlListeners = w;
}

uint WaterLevelSensor::getWaterLevel() const
{
    return m_waterLevel;
}

WaterLevelSensor::~WaterLevelSensor()
{}
