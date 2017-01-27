/*
 * WebSocket.h
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#ifndef INC_WEBSOCKET_H_
#define INC_WEBSOCKET_H_

#include <sys/types.h>
#include <vector>

#include "pRTOS.h"
#include "WasProBehCntr.h"
#include "WasProgUitvoerHandler.h"
#include "WasProgram.h"
#include "CurrentStatus.h"

class WebSocket : public RTOS::task
{
private:
	WasProBehCntr m_wbc;
	std::vector<WasProgram> m_wps;

	RTOS::flag m_wasProgramsFlag;
	RTOS::flag m_progresFlag;
	RTOS::pool< std::vector<WasProgram> > m_wasProgramsPool;
	RTOS::pool<CurrentStatus> m_progresPool;

	RTOS::clock m_clock;

	void main(void);
public:
	WebSocket(const uint prio, WasProgUitvoerHandler &wpUC);
	virtual ~WebSocket();

	void setWashPrograms(const std::vector<WasProgram> &wps);
	void setProgres(const CurrentStatus &cs);
};



#endif /* INC_WEBSOCKET_H_ */
