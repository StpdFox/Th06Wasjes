#include "WasProgUitvoerHandler.h"

WasProgUitvoerHandler::WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PassiveIOHandler &pasHandler) :
    task(prio, "WasProgUitvoerHandler"),
    m_tempSensor(tempSensor),
    m_waterLvlSensor(waterLvlSensor),
    //m_webSocked = webSocked,
    m_pasHandler(pasHandler),
    m_newTempFlag(this, "NewTempFlag"),
    m_newWLvlFlag(this, "newWLvlFlag"),
    m_tempPool("TempPool"),
    m_wLvlPool("WlvlPool"),
    m_wasPhase("WasPhase"),
    m_cancelTimer(this, "CancelTimer"),
    m_phaseTimer(this, "PhaseTimer"),
    m_wUC(m_pasHandler, *this)
{}

void WasProgUitvoerHandler::updateTemp(TempSensor *ts)
{
    m_temp = ts->getTemp();
    std::cout << "temp: " << m_temp << std::endl;
    set(m_newTempFlag);
}

void WasProgUitvoerHandler::updateWLevel(WaterLevelSensor *lvl)
{
    m_waterLvl = lvl->getWaterLevel();
    set(m_newWLvlFlag);
}

void WasProgUitvoerHandler::setWProgPhase(const WasProgramPhase &wPhase)
{
    m_wasPhase.write(wPhase);
}

void WasProgUitvoerHandler::setCancelTimer(const uint time)
{
    m_cancelTimer.set(time);
}

void WasProgUitvoerHandler::setPhaseTimer(const uint time)
{
    m_phaseTimer.set(time);
}

void WasProgUitvoerHandler::cancelCancelTimer()
{
    m_cancelTimer.cancel();
}

void WasProgUitvoerHandler::cancelPhaseTimer()
{
    m_phaseTimer.cancel();
}

void WasProgUitvoerHandler::main(void)
{
    m_tempSensor.setListener(this);
    m_waterLvlSensor.setListener(this);
    while(true)
    {
        if(wait() == m_newTempFlag) m_wUC.setNewTemp(m_temp);
        if(wait() == m_newWLvlFlag) m_wUC.setNewWLvl(m_waterLvl);
        if(wait() == m_cancelTimer) 
            {
                m_wUC.cancelTimeOver();
                std::cout << "cancel over time" << std::endl;
            }
        if(wait() == m_phaseTimer)
        {
            std::cout << "phase time cancle" << std::endl;
            m_wUC.phaseTimeOver();
        }
        m_wUC.checkWasMachine();
        
        
        
//        if(wait() == m_wasPhase)
//        {
//            m_wUC.setNewPhase(m_wasPhase.read());
//        }
        //suspend();
    }
}