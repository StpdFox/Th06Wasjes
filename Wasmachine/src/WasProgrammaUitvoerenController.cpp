#include "WasProgrammaUitvoerenController.h"

#include <stdlib.h>

WasProgrammaUitvoerenController::WasProgrammaUitvoerenController(PassiveIOHandler &pasIOHandler, WasProgUitvoerHandler &wPUH, PeriodiekeIOHandler &perIOHandler):
    m_pasIOHandler(pasIOHandler),
    m_wPUH(wPUH),
	m_perIOHandler(perIOHandler),
	m_logger(5)
{}

void WasProgrammaUitvoerenController::setNewPhase(const WasProgramPhase &wProgPhase)
{
    m_currentPhase = wProgPhase;
}

void WasProgrammaUitvoerenController::setNewTemp(const uint temp)
{
    m_currentTemp = temp;
}

void WasProgrammaUitvoerenController::setNewWLvl(const uint wLvl)
{
    m_wLevel = wLvl;
}

void WasProgrammaUitvoerenController::cancelTimeOver()
{
    m_cancelTimer = true;
}

void WasProgrammaUitvoerenController::phaseTimeOver()
{
    m_phaseTimer = true;
}

void WasProgrammaUitvoerenController::checkWasMachine()
{
    if(m_currentPhase.phase == NONE)
    {
    	m_logger.write("Phase if NONE");
    	if(!m_perIOHandSuspend)
    	{
			m_perIOHandler.suspend();
			m_perIOHandSuspend = true;
    	}

    	if(m_heaterOn) m_pasIOHandler.heaterOff();
    	if(m_waterValveOpen) m_pasIOHandler.closeWaterValve();
    	if(m_currentRPM) m_pasIOHandler.setMotoRPM(0);
    }
    else if(m_currentPhase.phase == SPOELEN)
    {
    	m_logger.write("Phase if SPOELEN");
    	if(m_perIOHandSuspend)
    	{
    		m_perIOHandler.resume();
    		m_perIOHandSuspend = false;
    	}
    }
    else if(m_currentPhase.phase == WASSEN)
    {
    	m_logger.write("Phase if WASSEN");
    	if(m_perIOHandSuspend)
    	{
    		m_perIOHandler.resume();
    		m_perIOHandSuspend = false;
    	}

        if(m_wLevel < m_targetWLevel) 
        {
            if(!m_waterValveOpen)
            {
                m_pasIOHandler.openWaterValve();
                m_waterValveOpen = true;
            }
        }
        else
        {
            if(m_waterValveOpen)
            {
               m_pasIOHandler.closeWaterValve();
                m_waterValveOpen = false;
            }
            
            if(m_currentTemp < m_currentPhase.temp) 
            {
                if(!m_heaterOn)
                {
                	m_pasIOHandler.heaterOn();
                    m_heaterOn = true;
                }
            }
            else                                    
            {
                if(m_heaterOn)
                {
                    m_pasIOHandler.heaterOff();
                    m_heaterOn = false;
                }
                else
                {
                    m_pasIOHandler.setMotoRPM(rand() % 1000);
                }
//                if(m_moterLeft)
//                {
//                    std::cout << "set new rpm left" << std::endl;
//                    m_moterLeft = false;
//                    message.motorRPM = 10;
//                    newMessage = true;
//                }
//                else
//                {
//                    std::cout << "set new rpm right" << std::endl;
//                    m_moterLeft = true;
//                    message.motorRPM = -10;
//                    newMessage = true;
//                }
//                std::cout << "out of" << std::endl;
            }
        }

    }
    else if((m_currentPhase.phase = CENTRIFUGEREN))
    {
    	m_logger.write("Phase if CENTRIFUGEREN");
    }

}
