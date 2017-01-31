/*
 * WasProBehCntr.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WasProBehCntr.h"
#include "WasProgram.h"
#include "WasProgUitvoerHandler.h"
#include "WebSocket.h"

WasProBehCntr::WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh, WebSocket &ws) :
	RTOS::task(prio, "wbc"),
	m_wh(wh),
	m_ws(ws),
	m_startWProgFlag(this, "MailFlag"),
	m_setNewWProgFlag(this, "NewProgFlag"),
	m_deleteWProgFlag(this, "DeleteProgFlag"),
	m_getWProgsFlag(this, "GetWProgsFlag"),
	m_startWProgBox("StartWProgMailBox"),
	m_setWProgBox("SetWprogBox"),
	m_deleteWProgBox("DeleteWProgBox"),
	m_phaseTimer(this, "PhaseTimer"),
	m_updateTimer(this, "UpdateTimer")
{
//	WasProgXml wpx;
//	WasProgram wp;
//	wp.RPM = 400;
//	wp.temp = 60;
//	wp.timeSpoelen = 50;
//	wp.timeWassing = 1223;
//	wp.timecentrifugeren = 234;
//	wpx.addNewWashProgram(wp);
//	wpx.deleteWashProgram(wp);
}

void WasProBehCntr::startWProg(const WasProgram &wp)
{
	//TODO The set of the m_mailFlag must be under the write off the pool.

	m_startWProgFlag.set();
	m_startWProgBox.write(wp);
//	m_mailFlag.set();
}

void WasProBehCntr::setWProg(const WasProgram &wp)
{
	std::cout << "set" << std::endl;
	m_setWProgBox.write(wp);
	m_setNewWProgFlag.set();
	std::cout << "done set" << std::endl;
}

void WasProBehCntr::deleteWProg(const WasProgram &wp)
{
	m_deleteWProgBox.write(wp);
	m_deleteWProgFlag.set();
}

void WasProBehCntr::changeWProg(const WasProgram &orWp, const WasProgram &newWp)
{

}

void WasProBehCntr::getWProgs()
{
	m_getWProgsFlag.set();
}

void WasProBehCntr::washing()
{
	if(m_currentWasProgramPhase.phase == NONE)
	{
		std::cout << "set washing" << std::endl;
		m_running = true;
		m_currentWasProgramPhase.phase = WASSEN;
		m_currentWasProgramPhase.temp = m_currentWasProgram.temp;
		m_wh.setWProgPhase(m_currentWasProgramPhase);
		m_phaseTimer.set(m_currentWasProgram.timeWassing S);
	}
	else if(m_currentWasProgramPhase.phase == WASSEN)
	{
		std::cout << "set spoeling" << std::endl;
		m_currentWasProgramPhase.phase = SPOELEN;
		m_currentWasProgramPhase.temp = 0;
		m_wh.setWProgPhase(m_currentWasProgramPhase);
		m_phaseTimer.set(m_currentWasProgram.timeSpoelen S);
	}
	else if(m_currentWasProgramPhase.phase == SPOELEN)
	{
		std::cout << "set centrifugeren" << std::endl;
		m_currentWasProgramPhase.phase = CENTRIFUGEREN;
		m_currentWasProgramPhase.RPM = m_currentWasProgram.RPM;
		m_wh.setWProgPhase(m_currentWasProgramPhase);
		m_phaseTimer.set(m_currentWasProgram.timecentrifugeren S);
	}
	else if(m_currentWasProgramPhase.phase == CENTRIFUGEREN)
	{
		std::cout << "set none" << std::endl;
		m_currentWasProgramPhase.phase = NONE;
		m_currentWasProgramPhase.RPM = 0;
		m_wh.setWProgPhase(m_currentWasProgramPhase);
		m_running = false;

		m_updateTimer.cancel();
		CurrentStatus cs;
		cs.phase = m_currentWasProgramPhase.phase;
		cs.timeRemaining = 0;
		m_ws.setProgres(cs);
	}
}

void WasProBehCntr::updateWebSocked()
{
	m_totalTime -= 60;
	CurrentStatus cs;
	cs.phase = m_currentWasProgramPhase.phase;
	cs.timeRemaining = m_totalTime;
	m_ws.setProgres(cs);
}

void WasProBehCntr::main(void)
{
	while(true)
	{
		RTOS::event ev =  wait(m_startWProgFlag + m_setNewWProgFlag + m_deleteWProgFlag + m_phaseTimer + m_updateTimer + m_getWProgsFlag);

		if(ev == m_startWProgFlag)
		{
			if(!m_running)
			{
				m_currentWasProgram = m_startWProgBox.read();
				m_totalTime = m_currentWasProgram.timeSpoelen + m_currentWasProgram.timeWassing + m_currentWasProgram.timecentrifugeren + 60;
				washing();
				updateWebSocked();
				m_updateTimer.set(60 S);
			}
			else m_startWProgBox.read();
		}
		else if(ev == m_setNewWProgFlag)
		{
			m_wpx.addNewWashProgram(m_setWProgBox.read());
			std::cout << "flag" << std::endl;
		}
		else if(ev == m_deleteWProgFlag)
		{
			m_wpx.deleteWashProgram(m_deleteWProgBox.read());
		}
		else if(ev == m_phaseTimer)
		{
			washing();
		}
		else if(ev == m_updateTimer)
		{
			updateWebSocked();
			m_updateTimer.set(60 S);
		}
		else if(ev == m_getWProgsFlag)
		{
			m_ws.setWashPrograms(m_wpx.getWashingPrograms());
		}
	}
}

WasProBehCntr::~WasProBehCntr()
{

}










