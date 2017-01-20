/*
 * WasProBehCntr.h
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#ifndef INC_WASPROBEHCNTR_H_
#define INC_WASPROBEHCNTR_H_

#include "pRTOS.h"
#include "WasProgram.h"
#include "WasProgXml.h"
#include "WasProgramPhase.h"

class WasProgUitvoerHandler;
class WebSocket;

class WasProBehCntr : public RTOS::task
{
private:
	WasProgUitvoerHandler &m_wh;
	WebSocket &m_ws;
	WasProgXml m_wpx;

	RTOS::flag m_startWProgFlag;
	RTOS::flag m_setNewWProgFlag;
	RTOS::flag m_deleteWProgFlag;
	RTOS::flag m_getWProgsFlag;

	RTOS::mailbox<WasProgram> m_startWProgBox;
	RTOS::mailbox<WasProgram> m_setWProgBox;
	RTOS::mailbox<WasProgram> m_deleteWProgBox;

	RTOS::timer m_phaseTimer;
	RTOS::timer m_updateTimer;

	WasProgram m_currentWasProgram;
	WasProgramPhase m_currentWasProgramPhase;

	bool m_running = false;
	uint m_totalTime = 0;

	void washing();
	void updateWebSocked();
	void main(void);
public:
	WasProBehCntr(const uint prio, WasProgUitvoerHandler &wh, WebSocket &ws);
	virtual ~WasProBehCntr();

	void startWProg(const WasProgram &wp);
	void setWProg(const WasProgram &wp);
	void deleteWProg(const WasProgram &wp);
	void changeWProg(const WasProgram &orWp, const WasProgram &newWp);

	void getWProgs();
};



#endif /* INC_WASPROBEHCNTR_H_ */
