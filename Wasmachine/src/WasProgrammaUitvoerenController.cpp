#include "WasProgrammaUitvoerenController.h"

WasProgrammaUitvoerenController::WasProgrammaUitvoerenController(PassiveIOHandler &pasIOHandler, WasProgUitvoerHandler &wPUH, PeriodiekeIOHandler &perIOHandler):
    m_pasIOHandler(pasIOHandler),
    m_wPUH(wPUH),
	m_perIOHandler(perIOHandler)
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

void WasProgrammaUitvoerenController::checkWasMachine()
{
    std::cout << "in check" << std::endl;
	if(m_currentPhase.phase == NONE)
	{
		std::cout << "doing none" << std::endl;
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
		if(!m_perIOHandSuspend)
		{
			m_perIOHandler.suspend();
			m_perIOHandSuspend = true;
		}

		if(m_heaterOn) m_pasIOHandler.heaterOff();
		if(m_waterValveOpen) m_pasIOHandler.closeWaterValve();
		if(m_currentRPM) m_pasIOHandler.setMotoRPM(0);
    }
    else if(m_currentPhase.phase == WASSEN)
    {
        //std::cout << "in wassen" << std::endl;
        //m_wPUH.setPhaseTimer(60000);
        //std::cout << "wlvl: " << m_wLevel << std::endl;
        if(m_wLevel < m_targetWLevel) 
        {
            if(!m_waterValveOpen)
            {
                //std::cout << "set valve open" << std::endl;
                //m_pIOHandler.lockDoor();
                m_pasIOHandler.openWaterValve();
                m_waterValveOpen = true;
                //m_pIOHandler.resume();
            }
        }
        else
        {
            if(m_waterValveOpen)
            {
                m_pasIOHandler.closeWaterValve();
                m_waterValveOpen = false;
                //m_pIOHandler.resume();
            }
            
            //std::cout << "currenttemp: " << m_currentTemp << std::endl;
            if(m_currentPhase.temp > m_currentTemp) 
            {
                if(!m_heaterOn)
                {
                    m_pasIOHandler.heaterOn();
                    m_heaterOn = true;
                    //m_pIOHandler.resume();
                }
            }
            else                                    
            {
                if(m_heaterOn)
                {
                    m_pasIOHandler.heaterOff();
                    m_heaterOn = false;
                    //m_pIOHandler.resume();
                }
                
//                if(m_moterLeft)
//                {
//                    m_moterLeft = false;
//                    m_pasIOHandler.setMotoRPM(10);
//                    //m_pIOHandler.resume();
//                }
//                else
//                {
//                    m_moterLeft = true;
//                    m_pasIOHandler.setMotoRPM(-10);
//                    //m_pIOHandler.resume();
//                }
            }
        }
    }
    else if(m_currentPhase.phase == CENTRIFUGEREN)
    {
        
    }
}
