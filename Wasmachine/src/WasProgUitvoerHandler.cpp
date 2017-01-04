#include "WasProgUitvoerHandler.h"

WasProgUitvoerHandler::WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PassiveIOHandler &pasHandler) :
    task(prio, "WasProgUitvoerHandler"),
    m_tempSensor(tempSensor),
    m_waterLvlSensor(waterLvlSensor),
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

void WasProgUitvoerHandler::main(void)
{
    m_tempSensor.setListener(this);
    m_waterLvlSensor.setListener(this);
    while(true)
    {
        //This will not work because it's not posible to wait on 2 or more flags only 1!!!
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
