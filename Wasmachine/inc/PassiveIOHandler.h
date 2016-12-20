#ifndef __PassiveIOHandler
#define __PassiveIOHandler

#include "pRTOS.h"

class PassiveIOHandler : public RTOS::task
{
private:
    RTOS::flag m_doorlockFlag;
    RTOS::flag m_doorUnlockFlag;
    RTOS::flag m_heaterOnFlag;
    RTOS::flag m_heaterOffFlag;
    RTOS::flag m_waterValveOpenFlag;
    RTOS::flag m_waterValveCloseFlag;
    RTOS::flag m_signalLedOnFlag;
    RTOS::flag m_signalLedOffFlag;
    RTOS::flag m_pumpOnFlag;
    RTOS::flag m_pumpOffFlag;
    RTOS::flag m_newRPMFlag;
    RTOS::pool m_motorRPMPool;
    
    DefaultOutput m_doorLock(2, 64, 128);
    DefaultOutput m_heater(7, 16, 32);
    DefaultOutput m_waterValve(3, 16, 32);
    DefaultOutput m_signalLed(11, 16, 32);
    DefaultOutput m_pump(5, 16, 32);
    Motor m_motor(10);
    
    void main();
public:
    PassiveIOHandler(const uint prio);
    
    void lockDoor() const;
    void unlockDoor() const;
    void heaterOn() const;
    void heaterOff() const;
    void openWaterValve() const;
    void closeWaterValve() const;
    void signalLedOn() const;
    void signalLedOff() const;
    void setMotoRPM() const;
    void pumpOn() const;
    void pumpOff() const;    
}

#endif