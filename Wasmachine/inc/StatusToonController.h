/*
 * StatusToonController.h
 *
 *  Created on: Jan 18, 2017
 *      Author: hendrik
 */

#ifndef INC_STATUSTOONCONTROLLER_H_
#define INC_STATUSTOONCONTROLLER_H_

#include <CurrentStatus.h>
#include <vector>

#include "WebSocket.h"
#include "WasProgram.h"

class StatusToonController : public RTOS::task
{
private:
	WebSocket &m_ws;

	RTOS::flag m_newProgramsFlag;
	RTOS::flag m_newStateFlag;

	RTOS::pool< std::vector<WasProgram> > m_wasProgramsPool;
	RTOS::pool<CurrentStatus> m_currentState;

	void main(void);
public:
	StatusToonController(WebSocket &ws);
	virtual ~StatusToonController();

	void setWasPrograms(const std::vector<WasProgram> &wps);
	void setNewStatus(const CurrentStatus &cs);
};



#endif /* INC_STATUSTOONCONTROLLER_H_ */
