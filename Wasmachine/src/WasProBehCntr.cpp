/*
 * WasProBehCntr.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WasProBehCntr.h"
#include "WasProgramPhase.h"
#include "WasProgram.h"
#include "WasProgXml.h"

WasProBehCntr::WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh) :
	RTOS::task(prio, "wbc"),
	m_wh(wh),
	m_mailFlag(this, "MailFlag"),
	m_startWProg("StartWProgMailBox"),
	m_phaseTimer(this, "PhaseTimer")
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

void WasProBehCntr::startWprog(const WasProgram &wp)
{
	//TODO The set of the m_mailFlag must be under the write off the pool.

	m_mailFlag.set();
	m_startWProg.write(wp);
//	m_mailFlag.set();
}

void WasProBehCntr::main(void)
{
	while(true)
	{
		wait(m_mailFlag);
		m_currentWasProgram = m_startWProg.read();
		WasProgramPhase wpp;
		wpp.phase = WASSEN;
		wpp.temp = m_currentWasProgram.temp;
		m_wh.setWProgPhase(wpp);
		m_phaseTimer.set(m_currentWasProgram.timeWassing S);
		wait(m_phaseTimer);
		wpp.phase = NONE;
		wpp.temp = 0;
		m_wh.setWProgPhase(wpp);
	}
}


