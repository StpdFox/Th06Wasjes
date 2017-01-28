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
	//m_waterLevel = m_uc.readUart(m_requestByte);
	//std::cout << "Water lvl: " << m_waterLevel << '%' << std::endl;
	//++m_waterLevel;
	//sleep(1);
	m_waterLevel = m_uc.readUart(6);
	std::cout << "water lvl: " << m_waterLevel << std::endl;
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
