#ifndef __WasProgUitvoerHandler
#define __WasProgUitvoerHandler

#include "pRTOS.h"
#include "TempSensor.h"
#include "TempListener.h"
#include "WaterLevelSensor.h"
#include "WaterLvlListener.h"
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
    
    RTOS::flag m_newValueFlag;
    RTOS::flag m_newPhaseFlag;
    RTOS::pool<uint> m_tempPool;
    RTOS::pool<uint> m_wLvlPool;
    RTOS::mailbox<WasProgramPhase> m_wasPhase;
    
    void main(void);
public:
    WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PassiveIOHandler &pasHandler);
    void updateTemp(TempSensor *ts);
    void updateWLevel(WaterLevelSensor *lvl);
    void setWProgPhase(const WasProgramPhase &wPhase);
};

#endif
