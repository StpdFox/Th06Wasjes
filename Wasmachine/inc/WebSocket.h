/*
 * WebSocket.h
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#ifndef INC_WEBSOCKET_H_
#define INC_WEBSOCKET_H_

#include <sys/types.h>

#include "pRTOS.h"
#include "WasProBehCntr.h"

class WebSocket : public RTOS::task
{
private:
	WasProBehCntr &m_wbc;
	void main(void);

public:
	WebSocket(const uint prio, WasProBehCntr &wbc);
};



#endif /* INC_WEBSOCKET_H_ */
