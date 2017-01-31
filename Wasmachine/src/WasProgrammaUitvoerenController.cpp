#include "WasProgrammaUitvoerenController.h"
#include "WasProgUitvoerHandler.h"

WasProgrammaUitvoerenController::WasProgrammaUitvoerenController(WasProgUitvoerHandler &wPUH, PeriodiekeIOHandler &perIOHandler, UartComs &uc):
    m_wPUH(wPUH),
	m_perIOHandler(perIOHandler),
	m_pasIOHandler(2, uc, wPUH),
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

void WasProgrammaUitvoerenController::timeOver()
{
	if(m_spinLeft)  m_spinLeft = false;
	else 			m_spinLeft = true;
	m_changeMoter = true;
}

void WasProgrammaUitvoerenController::clearPhase()
{
	if(m_currentRPM != 0)
	{
		m_pasIOHandler.setMotoRPM(0);
		m_currentRPM = 0;
	}

	if(m_wLevel > 0)
	{
		if(!m_pumpOn)
		{
			m_pasIOHandler.pumpOn();
			m_pumpOn = true;
		}
	}
	else
	{
		if(m_pumpOn)
		{
			m_pasIOHandler.pumpOff();
			m_pumpOn = false;
		}
		m_lastPhase = m_currentPhase.phase;
	}
}

void WasProgrammaUitvoerenController::checkWasMachine()
{
//	return;
	if(m_lastPhase != m_currentPhase.phase)
	{
		if(m_perIOHandSuspend)
		{
			m_perIOHandler.resume();
			m_perIOHandSuspend = false;
		}
		clearPhase();
	}
	else {
		if(m_currentPhase.phase == NONE)
		{
			//m_logger.write("Phase if NONE");
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
			m_currentRPM = 1;
			//m_logger.write("Phase if SPOELEN");
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

				if(m_changeMoter)
				{
				   if(m_spinLeft) 	m_pasIOHandler.setMotoRPM(m_currentRPM);
				   else				m_pasIOHandler.setMotoRPM(m_currentRPM + 128);
				   m_changeMoter = false;
				   m_wPUH.setWCUTimer(5 S);
				}
			}
		}
		else if(m_currentPhase.phase == WASSEN)
		{
			m_currentRPM = 1;
			//m_logger.write("Phase if WASSEN");
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
					else if(m_changeMoter)
					{
					   if(m_spinLeft) 	m_pasIOHandler.setMotoRPM(m_currentRPM);
					   else				m_pasIOHandler.setMotoRPM(m_currentRPM + 128);
					   m_changeMoter = false;
					   m_wPUH.setWCUTimer(5 S);
					}
				}
			}

		}
		else if((m_currentPhase.phase = CENTRIFUGEREN))
		{
			//m_logger.write("Phase if CENTRIFUGEREN");
			m_currentRPM = m_currentPhase.RPM;

			if(m_changeMoter)
			{
			   if(m_spinLeft) 	m_pasIOHandler.setMotoRPM(m_currentRPM);
			   else				m_pasIOHandler.setMotoRPM(m_currentRPM * -1);
			   m_changeMoter = false;
			   m_wPUH.setWCUTimer(5 S);
			}

			if(m_wLevel > 0)
			{
				if(!m_pumpOn)
				{
					m_pasIOHandler.pumpOn();
					m_pumpOn = true;
				}
			}
			else
			{
				if(m_pumpOn)
				{
					m_pasIOHandler.pumpOff();
					m_pumpOn = false;
				}
			}
		}
	}
}

void WasProgrammaUitvoerenController::error()
{
	m_currentPhase.phase = NONE;
	checkWasMachine();
	m_logger.write("Door not closed!");
	std::cout << "error!" << std::endl;
}












