#include "WasProgUitvoerHandler.h"

WasProgUitvoerHandler::WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PassiveIOHandler &pasHandler, PeriodiekeIOHandler &perHandler) :
    task(prio, "WasProgUitvoerHandler"),
    m_tempSensor(tempSensor),
    m_waterLvlSensor(waterLvlSensor),
    m_pasHandler(pasHandler),
    m_wUC(m_pasHandler, *this, perHandler),
    m_newTempFlag(this, "NewTempFlag"),
    m_newWLvlFlag(this, "newWLvlFlag"),
	m_newPhaseFlag(this, "newPhaseFlag"),
    m_tempPool("TempPool"),
    m_wLvlPool("WlvlPool"),
    m_wasPhase("WasPhase")
{
    std::cout << "PassiveIOHandler adress: " << &m_pasHandler << std::endl;
}

void WasProgUitvoerHandler::updateTemp(TempSensor *ts)
{
    m_tempPool.write(ts->getTemp());
    m_newTempFlag.set();
}

void WasProgUitvoerHandler::updateWLevel(WaterLevelSensor *lvl)
{
    m_wLvlPool.write(lvl->getWaterLevel());
    m_newWLvlFlag.set();
}

void WasProgUitvoerHandler::setWProgPhase(const WasProgramPhase &wPhase)
{
	std::cout << "going to set spul" << std::endl;
    m_wasPhase.write(wPhase);
    std::cout << "done setting stuff" << std::endl;
    m_newPhaseFlag.set();
    std::cout << "new phase ding gezet" << std::endl;
}

void WasProgUitvoerHandler::main(void)
{
    m_tempSensor.setListener(this);
    m_waterLvlSensor.setListener(this);

    while(true)
    {
    	wait(m_newPhaseFlag);
    	m_wUC.setNewPhase(m_wasPhase.read());

    	while(true)
    	{
    		RTOS::event ev = wait(m_newTempFlag + m_newWLvlFlag + m_newPhaseFlag);

    		if(ev == m_newTempFlag)
    		{
    			m_temp = m_tempPool.read();
    			m_wUC.setNewTemp(m_temp);
    		}
    		else if(ev == m_newWLvlFlag)
    		{
    			m_waterLvl = m_wLvlPool.read();
    			m_wUC.setNewWLvl(m_waterLvl);
    		}
    		else if(ev == m_newPhaseFlag)
    		{
    			WasProgramPhase wpp = m_wasPhase.read();
    			m_wUC.setNewPhase(wpp);
    			m_wUC.checkWasMachine();
    			if(wpp.phase == NONE) break;
    		}
    		m_wUC.checkWasMachine();
    	}
    }
}
















