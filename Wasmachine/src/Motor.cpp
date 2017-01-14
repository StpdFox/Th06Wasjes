#include <iostream>

#include "Motor.h"

Motor::Motor(const char startByte) : m_startByte(startByte)
{}

void Motor::setRPM(const uint RPM)
{
    std::cout << "set RPM to: " << RPM << std::endl;
}