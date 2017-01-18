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
#include "WasProgXml.h"

class WasProBehCntr : public RTOS::task
{
private:
	WasProgUitvoerHandler &m_wh;
	WasProgXml m_wpx;

	RTOS::flag m_startWProgFlag;
	RTOS::flag m_setNewWProgFlag;
	RTOS::flag m_deleteWProgFlag;


	RTOS::mailbox<WasProgram> m_startWProgBox;
	RTOS::mailbox<WasProgram> m_setWProgBox;
	RTOS::mailbox<WasProgram> m_deleteWProgBox;

	RTOS::timer m_phaseTimer;

	WasProgram m_currentWasProgram;

	void main(void);
public:
	WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh);
	virtual ~WasProBehCntr();

	void startWProg(const WasProgram &wp);
	void setWProg(const WasProgram &wp);
	void deleteWProg(const WasProgram &wp);
	void changeWProg(const WasProgram &orWp, const WasProgram &newWp);
};



#endif /* INC_WASPROBEHCNTR_H_ */
