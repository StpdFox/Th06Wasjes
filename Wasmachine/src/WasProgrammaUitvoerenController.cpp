#include "WasProgrammaUitvoerenController.h"
#include "PassiveIOMessage.h"
#include <stdlib.h>

WasProgrammaUitvoerenController::WasProgrammaUitvoerenController(PassiveIOHandler &pasIOHandler, WasProgUitvoerHandler &wPUH):
    m_pasIOHandler(pasIOHandler),
    m_wPUH(wPUH)
{
    m_currentPhase.phase = NONE;
    m_currentPhase.temp;
}

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
    PassiveIOMessage message;
    bool newMessage = false;
    if((m_currentPhase.phase = NONE))
    {
//    	if(!m_perIOHandSuspend)
//    	{
//			m_pasIOHandler.suspend();
//			m_perIOHandSuspend = true;
//    	}
    }

    if((m_currentPhase.phase = SPOELEN))
    {
//    	if(m_perIOHandSuspend)
//    	{
//    		m_pasIOHandler
//    	}
    }
    else if((m_currentPhase.phase = WASSEN))
    {
        if(m_wLevel < m_targetWLevel) 
        {
            if(!m_waterValveOpen)
            {
                message.waterValve = 1;
                newMessage = true;
                m_waterValveOpen = true;
            }
        }
        else
        {
            if(m_waterValveOpen)
            {
                message.waterValve = 0;
                newMessage = true;
                m_waterValveOpen = false;
            }
            
            if(m_currentTemp < m_currentPhase.temp) 
            {
                if(!m_heaterOn)
                {
                    message.heater = 1;
                    newMessage = true;
                    m_heaterOn = true;
                }
            }
            else                                    
            {
                if(m_heaterOn)
                {
                    std::cout << "heater off set" << std::endl;
                    message.heater = 0;
                    newMessage = true;
                    m_heaterOn = false;
                }
                else
                {
                    message.motorRPM = rand() % 1000;
                    newMessage = true;
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

        if(newMessage)
        {
            m_pasIOHandler.newMessage(message);
            //std::cout << "sleep " << std::endl;
            //sleep(1);
           // std::cout << "done sleping" << std::endl;
            m_pasIOHandler.setMessageFlag();
            
        }
    }
    else if((m_currentPhase.phase = CENTRIFUGEREN))
    {
        
    }
}
