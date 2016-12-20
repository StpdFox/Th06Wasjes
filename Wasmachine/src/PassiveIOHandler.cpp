#include <iostream>
#include "PassiveIOHandler.h"

PassiveIOHandler::PassiveIOHandler(const uint prio) : 
    task(prio, "PassIOHandler")
{}

PassiveIOHandler::lockDoor() const
{
    std::cout << "Lock door" << std::endl;
}

PassiveIOHandler::unlockDoor() const
{
    std::cout << "Unlock door" << std::endl;
}

PassiveIOHandler::heaterOn() const
{
    std::cout << "Heater on" << std::endl;
}

PassiveIOHandler::heaterOff() const
{
    std::cout << "Heater off" << std::endl;
}

PassiveIOHandler::openWaterValve() const
{
    std::cout << "Open water valve" << std::endl;
}

PassiveIOHandler::closeWaterValve() const
{
    std::cout << "Close water valve" << std::endl;
}

PassiveIOHandler::signalLedOn() const
{
    std::cout << "Signal led on" << std::endl;
}

PassiveIOHandler::signalLedOff() const
{
    std::cout << "Signal led off" << std::endl;
}

PassiveIOHandler::setMotoRPM(uint RPM) const
{
    std::cout << "New RPM: " << RPM << std::endl;
}

PassiveIOHandler::pumpOn() const
{
    std::cout << "Pump on: " << std::endl;
}

PassiveIOHandler::pumpOff() const
{
    std::cout << "Pump off: " << std::endl;
}

PassiveIOHandler::main()
{
    
}