#ifndef __WasProgUitvoerHandler
#define __WasProgUitvoerHandler

#include <vector>

#include "pRTOS.h"
#include "TempSensor.h"
#include "TempListener.h"
#include "WaterLevelSensor.h"
#include "WaterLvlListener.h"
#include "WasProgrammaUitvoerenController.h"
#include "WasProgramPhase.h"
#include "PassiveIOHandler.h"

class UartComs;

class WasProgUitvoerHandler : public RTOS::task, public TempListener, public WaterLvlListener
{
private:
    TempSensor &m_tempSensor;
    WaterLevelSensor &m_waterLvlSensor;
    
    //StatusToonController m_sTC;
    WasProgrammaUitvoerenController m_wUC;
    
    RTOS::flag m_newValueFlag;
    RTOS::flag m_newPhaseFlag;
    RTOS::flag m_passiveErrorFlag;
    RTOS::pool<uint> m_tempPool;
    RTOS::pool<uint> m_wLvlPool;
    RTOS::pool<WasProgramPhase> m_wasPhase;

    RTOS::timer m_wCUTimer;

    uint m_temp = 0;
    uint m_waterLvl = 0;

    void main(void);
public:
    WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PeriodiekeIOHandler &perHandler, UartComs &uc);
    virtual ~WasProgUitvoerHandler();

    void updateTemp(TempSensor *ts);
    void updateWLevel(WaterLevelSensor *lvl);
    void setWProgPhase(const WasProgramPhase &wPhase);
    void setWCUTimer(const uint time);
    void setErrorFlag();
};

#endif
