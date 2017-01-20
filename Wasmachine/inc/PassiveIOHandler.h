#ifndef __PassiveIOHandler
#define __PassiveIOHandler

#include "pRTOS.h"
#include "DefaultOutput.h"
#include "Motor.h"
#include "UartComs.h"

class PassiveIOHandler : public RTOS::task
{
private:
	UartComs &m_uc;

    RTOS::flag m_doorLockFlag;
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
    RTOS::pool<int> m_motorRPMPool;
    
    DefaultOutput m_doorLock;
    DefaultOutput m_heater;
    DefaultOutput m_waterValve;
    DefaultOutput m_signalLed;
    DefaultOutput m_pump;
    Motor m_motor;
    
    void main(void);
public:
    PassiveIOHandler(const uint prio, UartComs &uc);
    virtual ~PassiveIOHandler();

    void lockDoor();
    void unlockDoor();
    void heaterOn();
    void heaterOff();
    void openWaterValve();
    void closeWaterValve();
    void signalLedOn();
    void signalLedOff();
    void setMotoRPM(const int RPM);
    void pumpOn();
    void pumpOff();
};

#endif
