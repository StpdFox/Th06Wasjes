#include "WasProgUitvoerHandler.h"

WasProgUitvoerHandler::WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PassiveIOHandler &pasHandler) :
    task(prio, "WasProgUitvoerHandler"),
    m_tempSensor(tempSensor),
    m_waterLvlSensor(waterLvlSensor),
    //m_webSocked = webSocked,
    m_pasHandler(pasHandler),
    m_wUC(m_pasHandler, *this),
    m_newValueFlag(this, "NewTempFlag"),
	m_newPhaseFlag(this, "newPhaseFlag"),
    m_tempPool("TempPool"),
    m_wLvlPool("WlvlPool"),
    m_wasPhase("WasPhase"),
    m_cancelTimer(this, "CancelTimer"),
    m_phaseTimer(this, "PhaseTimer")
{
    std::cout << "PassiveIOHandler adress: " << &m_pasHandler << std::endl;
}

void WasProgUitvoerHandler::updateTemp(TempSensor *ts)
{
    m_tempPool.write(ts->getTemp());
    //m_newValueFlag.set();
}

void WasProgUitvoerHandler::updateWLevel(WaterLevelSensor *lvl)
{
    m_wLvlPool.write(lvl->getWaterLevel());
    m_newValueFlag.set();
}

void WasProgUitvoerHandler::setWProgPhase(const WasProgramPhase &wPhase)
{
    m_wasPhase.write(wPhase);
    m_newPhaseFlag.set();
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
        if(wait() == m_newValueFlag)
        {
			m_temp = m_tempPool.read();
			m_waterLvl = m_wLvlPool.read();
			m_wUC.setNewTemp(m_temp);
			m_wUC.setNewWLvl(m_waterLvl);
			m_wUC.checkWasMachine();
        }

        if(wait() == m_newPhaseFlag)
        {
        	m_wUC.setNewPhase(m_wasPhase.read());
        }
    }
}
