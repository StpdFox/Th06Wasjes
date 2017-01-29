#include "WaterLevelSensor.h"
#include <iostream>
#include <unistd.h>

WaterLevelSensor::WaterLevelSensor(const char *reqByte, UartComs &uc) :
	m_uc(uc),
	m_requestByte(reqByte),
	m_wlvlListeners(nullptr)
{}

void WaterLevelSensor::readWaterLevel()
{
	m_waterLevel = m_uc.readUart(6);
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
