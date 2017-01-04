#ifndef __PassiveIOHandler
#define __PassiveIOHandler

#include "pRTOS.h"
#include "DefaultOutput.h"
#include "Motor.h"
#include "PassiveIOMessage.h"

class PassiveIOHandler : public RTOS::task
{
private:
    RTOS::flag m_newActionFlag;
    RTOS::pool<PassiveIOMessage> m_messagePool;
    
    DefaultOutput m_doorLock;
    DefaultOutput m_heater;
    DefaultOutput m_waterValve;
    DefaultOutput m_signalLed;
    DefaultOutput m_pump;
    Motor m_motor;
    
    void main(void);
public:
    PassiveIOHandler(const uint prio);
    void newMessage(const PassiveIOMessage &message);
};

#endif