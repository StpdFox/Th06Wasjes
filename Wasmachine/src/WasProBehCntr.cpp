/*
 * WasProBehCntr.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WasProBehCntr.h"
#include "WasProgramPhase.h"
#include "WasProgXml.h"

WasProBehCntr::WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh) :
	RTOS::task(prio, "wbc"),
	m_wh(wh),
	m_mailFlag(this, "MailFlag"),
	m_startWProg("StartWProgMailBox"),
	m_phaseTimer(this, "PhaseTimer")
{
	m_phaseTimer.set(10000 S);
	WasProgXml wpx;
}

void WasProBehCntr::startWprog(const WasProgram &wp)
{

//	m_mailFlag.set();
	std::cout << "flag had bene set" << std::endl;
	m_startWProg.write(wp);
	std::cout << "going to set flag" << std::endl;
	m_mailFlag.set();

	std::cout << "Flag has been set W prog" << std::endl;
}

void WasProBehCntr::main(void)
{
	while(true)
	{
		std::cout << "WasProgramBeheerController waiting for flag" << std::endl;
		wait(m_mailFlag + m_phaseTimer);
		sleep(500);
		std::cout << "WasProgramBeheerController flag has been set" << std::endl;
		m_currentWasProgram = m_startWProg.read();
		std::cout << "done reading mail" << std::endl;
		WasProgramPhase wpp;
		wpp.phase = WASSEN;
		wpp.temp = m_currentWasProgram.temp;
		std::cout << "writing to handler" << std::endl;
		m_wh.setWProgPhase(wpp);
		std::cout << "WasProgramBeheerController timer has been set" << std::endl;
		m_phaseTimer.set(m_currentWasProgram.timeWassing S);
		std::cout << "WasProgramBeheerController done setting other stuff now waiting" << std::endl;
		wait(m_phaseTimer);
		wpp.phase = NONE;
		wpp.temp = 0;
		m_wh.setWProgPhase(wpp);
	}
}


