#include <iostream>
#include "PassiveIOHandler.h"

PassiveIOHandler::PassiveIOHandler(const uint prio) : 
    task(prio, "PassIOHandler"),
    m_newActionFlag(this, "messageFlag"),
    m_messagePool("messagePool"),
    m_doorLock(DefaultOutput(2, 64, 128)),
    m_heater(DefaultOutput(7, 16, 32)),
    m_waterValve(DefaultOutput(3, 16, 32)),
    m_signalLed(DefaultOutput(11, 16, 32)),
    m_pump(DefaultOutput(5, 16, 32)),
    m_motor(Motor(10))
{}

void PassiveIOHandler::newMessage(const PassiveIOMessage &message)
{
    m_messagePool.write(message);
    m_newActionFlag.set();
}

void PassiveIOHandler::main(void)
{
    PassiveIOMessage message;
    int currentMoterRPM = 0;
    while(true)
    {
        wait(m_newActionFlag);
        message = m_messagePool.read();
        m_newActionFlag.clear();
        
        if(message.doorLock == 1)           std::cout << "Door locked" << std::endl;
        else if(message.doorLock == 0)      std::cout << "Door unlocked" << std::endl;
        
        if(message.heater == 1)             std::cout << "Heater on" << std::endl;
        else if(message.heater == 0)        std::cout << "Heater off" << std::endl;
        
        if(message.pump == 1)               std::cout << "Pump on" << std::endl;
        else if(message.pump == 0)          std::cout << "Pump off" << std::endl;
        
        if(message.signalLed == 1)          std::cout << "Signal led on" << std::endl;
        else if(message.signalLed == 0)     std::cout << "Signal led off" << std::endl;
        
        if(message.waterValve == 1)         std::cout << "Water valve open" << std::endl;
        else if(message.waterValve == 0)    std::cout << "Water valve closed" << std::endl;
        
        if(message.motorRPM != currentMoterRPM)
        {
            std::cout << "set motor RPM to: " << message.motorRPM << std::endl;
            currentMoterRPM = message.motorRPM;
        }
    }
}