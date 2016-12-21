#include "WasProgrammaUitvoerenController.h"

WasProgrammaUitvoerenController::WasProgrammaUitvoerenController(PassiveIOHandler &pasIOHandler, WasProgUitvoerHandler &wPUH):
    m_pIOHandler(pasIOHandler),
    m_wPUH(wPUH)
{
    m_currentPhase.phase = WASSEN;
    m_currentPhase.temp = 50;
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
    std::cout << "in check" << std::endl;
    if(m_currentPhase.phase = SPOELEN)
    {
        
    }
    else if(m_currentPhase.phase = WASSEN)
    {
        std::cout << "in wassen" << std::endl;
        //m_wPUH.setPhaseTimer(60000);
        std::cout << "wlvl: " << m_wLevel << std::endl;
        if(m_wLevel < m_targetWLevel) 
        {
            if(!m_waterValveOpen)
            {
                std::cout << "set valve open" << std::endl;
                m_pIOHandler.lockDoor();
                m_pIOHandler.openWaterValve();
                m_waterValveOpen = true;
            }
        }
        else
        {
            if(m_waterValveOpen)
            {
                m_pIOHandler.closeWaterValve();
                m_waterValveOpen = false;
            }
            
            std::cout << "currenttemp: " << m_currentTemp << std::endl;
            if(m_currentPhase.temp > m_currentTemp) 
            {
                if(!m_heaterOn)
                {
                    m_pIOHandler.heaterOn();
                    m_heaterOn = true;
                }
            }
            else                                    
            {
                if(m_heaterOn)
                {
                    m_pIOHandler.heaterOff();
                    m_heaterOn = false;
                }
                
                if(m_moterLeft)
                {
                    m_moterLeft = false;
                    m_pIOHandler.setMotoRPM(10);
                }
                else
                {
                    m_moterLeft = true;
                    m_pIOHandler.setMotoRPM(-10);
                }
            }
        }
    }
    else if(m_currentPhase.phase = CENTRIFUGEREN)
    {
        
    }
}