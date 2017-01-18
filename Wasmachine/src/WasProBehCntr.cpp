/*
 * WasProBehCntr.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WasProBehCntr.h"
#include "WasProgramPhase.h"
#include "WasProgram.h"

WasProBehCntr::WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh) :
	RTOS::task(prio, "wbc"),
	m_wh(wh),
	m_startWProgFlag(this, "MailFlag"),
	m_setNewWProgFlag(this, "NewProgFlag"),
	m_deleteWProgFlag(this, "DeleteProgFlag"),
	m_startWProgBox("StartWProgMailBox"),
	m_setWProgBox("SetWprogBox"),
	m_deleteWProgBox("DeleteWProgBox"),
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

void WasProBehCntr::startWProg(const WasProgram &wp)
{
	//TODO The set of the m_mailFlag must be under the write off the pool.

	m_startWProgFlag.set();
	m_startWProgBox.write(wp);
//	m_mailFlag.set();
}

void WasProBehCntr::setWProg(const WasProgram &wp)
{
	m_setWProgBox.write(wp);
	m_setNewWProgFlag.set();
}

void WasProBehCntr::deleteWProg(const WasProgram &wp)
{
	m_deleteWProgBox.writer(wp);
	m_deleteWProgFlag.set();
}

void WasProBehCntr::changeWProg(const WasProgram &orWp, const WasProgram &newWp)
{

}

void WasProBehCntr::main(void)
{
	while(true)
	{
		RTOS::event ev =  wait(m_startWProgFlag + m_setNewWProgFlag + m_deleteWProgFlag);

		if(ev == m_startWProgFlag)
		{
			m_currentWasProgram = m_startWProgBox.read();
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
		else if(ev == m_setNewWProgFlag)
		{
			m_wpx.addNewWashProgram(m_setWProgBox.read());
		}
		else if(ev == m_deleteWProgFlag)
		{
			m_wpx.deleteWashProgram(m_deleteWProgBox.read());
		}
	}
}


