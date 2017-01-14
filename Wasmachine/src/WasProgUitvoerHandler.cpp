#include "WasProgUitvoerHandler.h"

WasProgUitvoerHandler::WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor, PassiveIOHandler &pasHandler, PeriodiekeIOHandler &perHandler) :
    task(prio, "WasProgUitvoerHandler"),
    m_tempSensor(tempSensor),
    m_waterLvlSensor(waterLvlSensor),
    m_pasHandler(pasHandler),
    m_wUC(m_pasHandler, *this, perHandler),
    m_newValueFlag(this, "NewTempFlag"),
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
    //m_newValueFlag.set();
}

void WasProgUitvoerHandler::updateWLevel(WaterLevelSensor *lvl)
{
    m_wLvlPool.write(lvl->getWaterLevel());
    m_newValueFlag.set();
}

void WasProgUitvoerHandler::setWProgPhase(const WasProgramPhase &wPhase)
{
	std::cout << "phase flag have been set" << std::endl;
    m_wasPhase.write(wPhase);
    if(!m_running) m_newPhaseFlag.set();
}

void WasProgUitvoerHandler::main(void)
{
    m_tempSensor.setListener(this);
    m_waterLvlSensor.setListener(this);

    uint currentPhaseMessageNumber = 0;

    while(true)
    {
    	std::cout << "waiting for phase flag" << std::endl;
    	wait(m_newPhaseFlag);
    	currentPhaseMessageNumber = m_wasPhase.read().number;
    	std::cout << "done waiting for phase flag" << std::endl;
    	m_wUC.setNewPhase(m_wasPhase.read());
    	m_wUC.checkWasMachine();
    	m_running = true;
    	while(true)
    	{
    	   wait(m_newValueFlag);
    	   m_temp = m_tempPool.read();
    	   m_waterLvl = m_wLvlPool.read();
    	   m_wUC.setNewTemp(m_temp);
    	   m_wUC.setNewWLvl(m_waterLvl);
    	   m_wUC.checkWasMachine();

           if(m_wasPhase.read().number != currentPhaseMessageNumber)
           {
        	   WasProgramPhase wpp = m_wasPhase.read();
        	   m_wUC.setNewPhase(wpp);
        	   m_wUC.checkWasMachine();
        	   if(wpp.phase == NONE)
        	   {
        		   m_running = false;
        		   break;
        	   }
           }
    	}
    	std::cout << "out of the sensor while" << std::endl;
    }
}
