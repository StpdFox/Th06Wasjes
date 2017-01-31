#include "WasProgUitvoerHandler.h"

WasProgUitvoerHandler::WasProgUitvoerHandler(const uint prio, TempSensor &tempSensor, WaterLevelSensor &waterLvlSensor,
											 PeriodiekeIOHandler &perHandler, UartComs &uc) :
    task(prio, "WasProgUitvoerHandler"),
    m_tempSensor(tempSensor),
    m_waterLvlSensor(waterLvlSensor),
    m_wUC(*this, perHandler, uc),
    m_newValueFlag(this, "NewValueFlag"),
	m_newPhaseFlag(this, "newPhaseFlag"),
	m_passiveErrorFlag(this, "ErrorFlag"),
    m_tempPool("TempPool"),
    m_wLvlPool("WlvlPool"),
    m_wasPhase("WasPhase"),
	m_wCUTimer(this, "wCUTimer")
{}

void WasProgUitvoerHandler::updateTemp(TempSensor *ts)
{
    m_tempPool.write(ts->getTemp());
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

void WasProgUitvoerHandler::setWCUTimer(const uint time)
{
	m_wCUTimer.set(time);
}

void WasProgUitvoerHandler::main(void)
{
    m_tempSensor.setListener(this);
    m_waterLvlSensor.setListener(this);

    while(true)
    {
    	wait(m_newPhaseFlag);
    	m_wUC.setNewPhase(m_wasPhase.read());
    	m_wUC.checkWasMachine();
    	while(true)
    	{
    		RTOS::event ev = wait(m_newValueFlag + m_newPhaseFlag + m_wCUTimer + m_passiveErrorFlag);
    		if(ev == m_newValueFlag)
    		{
    	    	m_temp = m_tempPool.read();
    	    	m_waterLvl = m_wLvlPool.read();
    	    	m_wUC.setNewTemp(m_temp);
    	    	m_wUC.setNewWLvl(m_waterLvl);
    	    	m_wUC.checkWasMachine();
    		}
    		else if(ev == m_newPhaseFlag)
    		{
        	   WasProgramPhase wpp = m_wasPhase.read();
        	   m_wUC.setNewPhase(wpp);
        	   m_wUC.checkWasMachine();
        	   if(wpp.phase == NONE)
        	   {
        		   break;
        	   }
    		}
    		else if(ev == m_wCUTimer)
    		{
    			m_wUC.timeOver();
    		}
    		else if(ev == m_passiveErrorFlag)
    		{
    			m_wUC.error();
    		}
    	}
    }
}

void WasProgUitvoerHandler::setErrorFlag()
{
	m_passiveErrorFlag.set();
}

WasProgUitvoerHandler::~WasProgUitvoerHandler()
{}
