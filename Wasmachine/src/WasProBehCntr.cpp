/*
 * WasProBehCntr.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WasProBehCntr.h"
#include "WasProgramPhase.h"

WasProBehCntr::WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh) :
	RTOS::task(prio, "wbc"),
	m_wh(wh),
	m_mailFlag(this, "MailFlag"),
	m_startWProg("StartWProgMailBox"),
	m_phaseTimer(this, "PhaseTimer")
{}

void WasProBehCntr::startWprog(const WasProgram &wp)
{

	m_mailFlag.set();
	m_startWProg.write(wp);
//	m_mailFlag.set();

	std::cout << "Flag has been set" << std::endl;
}

void WasProBehCntr::main(void)
{
	while(true)
	{
		std::cout << "WasProgramBeheerController waiting for flag" << std::endl;
		wait(m_mailFlag);
		std::cout << "WasProgramBeheerController flag has been set" << std::endl;
		m_currentWasProgram = m_startWProg.read();
		std::cout << "done reading mail" << std::endl;
		WasProgramPhase wpp;
		wpp.phase = WASSEN;
		wpp.temp = m_currentWasProgram.temp;
		wpp.number = 1;
		std::cout << "writing to handler" << std::endl;
		m_wh.setWProgPhase(wpp);
		std::cout << "WasProgramBeheerController timer has been set" << std::endl;
		m_phaseTimer.set(m_currentWasProgram.timeWassing S);
		std::cout << "WasProgramBeheerController done setting other stuff now waiting" << std::endl;
		wait(m_phaseTimer);
		wpp.phase = NONE;
		wpp.temp = 0;
		wpp.number = 2;
		m_wh.setWProgPhase(wpp);
	}
}


