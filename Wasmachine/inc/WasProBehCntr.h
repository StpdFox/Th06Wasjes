/*
 * WasProBehCntr.h
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#ifndef INC_WASPROBEHCNTR_H_
#define INC_WASPROBEHCNTR_H_

#include "WasProgUitvoerHandler.h"
#include "WebSocket.h"
#include "WasProgram.h"

class WasProBehCntr : public RTOS::task
{
private:
	WasProgUitvoerHandler &m_wh;
	WebSocket &m_ws;

	RTOS::flag m_mailFlag;
	RTOS::mailbox m_newWProg;
	RTOS::mailbox m_startWProg;

	RTOS::timer m_phaseTimer;

	WasProgram m_currentWasProgram;

	void main(void);
public:
	WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh, WebSocket &ws);
	void getWprogs();
	void setWprog(const WasProgram &wp);
	void startWprog(const WasProgram &wp);
};



#endif /* INC_WASPROBEHCNTR_H_ */
