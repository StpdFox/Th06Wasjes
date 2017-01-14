#ifndef __WasProgUitvoerHandler
#define __WasProgUitvoerHandler

#include "pRTOS.h"
#include "TempSensor.h"
#include "TempListener.h"
#include "WaterLevelSensor.h"
#include "WaterLvlListener.h"
//#include "WebSocked.h"
//#include "StatusTonenController.h"
#include "WasProgrammaUitvoerenController.h"
#include "WasProgramPhase.h"
#include "PassiveIOHandler.h"

class WasProgUitvoerHandler : public RTOS::task, public TempListener, public WaterLvlListener
{
private:
    TempSensor &m_tempSensor;
    WaterLevelSensor &m_waterLvlSensor;
    PassiveIOHandler &m_pasHandler;
    
    //StatusTonenController m_sTC;
    WasProgrammaUitvoerenController m_wUC;
    
    RTOS::flag m_newTempFlag;
    RTOS::flag m_newWLvlFlag;
    RTOS::flag m_newPhaseFlag;
    RTOS::pool<uint> m_tempPool;
    RTOS::pool<uint> m_wLvlPool;
    RTOS::pool<WasProgramPhase> m_wasPhase;
    
    uint m_temp = 0;
    uint m_waterLvl = 0;
    
    void main(void);
public:
    WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PassiveIOHandler &pasHandler, PeriodiekeIOHandler &perHandler);
    void updateTemp(TempSensor *ts);
    void updateWLevel(WaterLevelSensor *lvl);
    void setWProgPhase(const WasProgramPhase &wPhase);
};

#endif
