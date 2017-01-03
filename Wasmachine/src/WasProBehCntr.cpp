/*
 * WasProBehCntr.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WasProBehCntr.h"

WasProBehCntr::WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh, WebSocket &ws) :
	RTOS::task(prio, "wbc"),
	m_wh(wh),
	m_ws(ws),
	m_mailFlag(this, "MailFlag"),
	m_newWProg("NewWProgMailBox"),
	m_startWProg("StartWProgMailBox")
{}

void WasProBehCntr::getWprogs()
{

}

void WasProBehCntr::setWprog(const WasProgram &wp)
{
	m_newWProg.write(wp);
	//m_mailFlag.set();
}

void WasProBehCntr::startWprog(const WasProgram &wp)
{
	m_startWProg.write(wp);
	m_mailFlag.set();
}

void WasProBehCntr::main(void)
{

}


