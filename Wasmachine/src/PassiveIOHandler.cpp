#include <iostream>
#include "PassiveIOHandler.h"

PassiveIOHandler::PassiveIOHandler(const uint prio) : 
    task(prio, "PassIOHandler"),
    m_doorLockFlag(this, "DoorLockFlag"),
    m_doorUnlockFlag(this, "DoorUnLockFlag"),
    m_heaterOnFlag(this, "HeaterOnFlag"),
    m_heaterOffFlag(this, "HeaterOffFlag"),
    m_waterValveOpenFlag(this, "WaterValveOpenFlag"),
    m_waterValveCloseFlag(this, "WaterValveCloseFlag"),
    m_signalLedOnFlag(this, "SignalLedOnFlag"),
    m_signalLedOffFlag(this, "SignalLedOffFlag"),
    m_pumpOnFlag(this, "PumpOnFlag"),
    m_pumpOffFlag(this, "PumpOffFlag"),
    m_newRPMFlag(this, "NewRPMFlag"),
    m_motorRPMPool("MotorRPMPool"),
    m_doorLock(DefaultOutput(2, 64, 128)),
    m_heater(DefaultOutput(7, 16, 32)),
    m_waterValve(DefaultOutput(3, 16, 32)),
    m_signalLed(DefaultOutput(11, 16, 32)),
    m_pump(DefaultOutput(5, 16, 32)),
    m_motor(Motor(10))
{}

void PassiveIOHandler::lockDoor()
{
   set(m_doorLockFlag);
}

void PassiveIOHandler::unlockDoor()
{
    set(m_doorUnlockFlag);
}

void PassiveIOHandler::heaterOn()
{
    set(m_heaterOnFlag);
}

void PassiveIOHandler::heaterOff()
{
    set(m_heaterOffFlag);
}

void PassiveIOHandler::openWaterValve()
{
    //std::cout << "set flag" << std::endl;
    //set(m_waterValveOpenFlag);
    m_waterValveOpenFlag.set();
}

void PassiveIOHandler::closeWaterValve()
{
    std::cout << "set flag" << std::endl;
    set(m_waterValveCloseFlag);
}

void PassiveIOHandler::signalLedOn()
{
    set(m_signalLedOnFlag);
}

void PassiveIOHandler::signalLedOff()
{
    set(m_signalLedOffFlag);
}

void PassiveIOHandler::setMotoRPM(const int RPM)
{
    m_motorRPMPool.write(RPM);
    set(m_newRPMFlag);
}

void PassiveIOHandler::pumpOn()
{
    set(m_pumpOnFlag);
}

void PassiveIOHandler::pumpOff()
{
    set(m_pumpOffFlag);
}

void PassiveIOHandler::main(void)
{
    while(true)
    {
//        std::cerr << "suspend" << std::endl;
//        RTOS::task::suspend();
//        std::cerr << "resume" << std::endl;
        //std::cout << "passive" << std::endl;
//        if(wait() == m_doorLockFlag)
//        {
//            m_doorLockFlag.clear();
//            std::cerr << "Door locked" << std::endl;
//        }
//        
//        if(wait() == m_doorUnlockFlag)
//        {
//            std::cerr << "Door unlocked" << std::endl;
//        }
//        
//        if(wait() == m_heaterOnFlag)
//        {
//            std::cerr << "Heater on" << std::endl;
//        }
//        
//        if(wait() == m_heaterOffFlag)
//        {
//            std::cerr << "Heater off" << std::endl;
//        }
        if(wait() == m_waterValveOpenFlag)
        {
            std::cerr << "Water valve open" << std::endl;
        }
        if(wait() == m_waterValveCloseFlag)
        {
            std::cerr << "Water valve closed" << std::endl;
        }
        
//        if(wait() == m_signalLedOnFlag)
//        {
//            std::cerr << "Signal led on" << std::endl;
//        }
//        
//        if(wait() == m_signalLedOffFlag)
//        {
//            std::cerr << "Signal led off" << std::endl;
//        }
//        
//        if(wait() == m_newRPMFlag)
//        {
//            std::cout << "Set motor on: " << m_motorRPMPool.read() << " RPM" << std::endl;
//        }
//        
//        if(wait() == m_pumpOnFlag)
//        {
//            std::cout << "Pump on" << std::endl;
//        }
//        
//        if(wait() == m_pumpOffFlag)
//        {
//            std::cout << "Pump off" << std::endl;
//        }
    }
}