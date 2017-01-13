/*
 * WasProBehCntr.h
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#ifndef INC_WASPROBEHCNTR_H_
#define INC_WASPROBEHCNTR_H_

#include "pRTOS.h"
#include "WasProgUitvoerHandler.h"
#include "WasProgram.h"

class WasProBehCntr : public RTOS::task
{
private:
	WasProgUitvoerHandler &m_wh;

	RTOS::flag m_mailFlag;
	RTOS::mailbox<WasProgram> m_startWProg;
	RTOS::timer m_phaseTimer;

	WasProgram m_currentWasProgram;

	void main(void);
public:
	WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh);
	void startWprog(const WasProgram &wp);
};



#endif /* INC_WASPROBEHCNTR_H_ */
