/*
 * WebSocket.h
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#ifndef INC_WEBSOCKET_H_
#define INC_WEBSOCKET_H_

#include "pRTOS.h"

class WebSocket : public RTOS::task
{
private:
	RTOS::flag m_updateSiteFlag;
	RTOS::pool m_wasProgsPool;
	RTOS::pool m_statusWasmachinePool;
	RTOS::pool m_statusBeheerPool;

	void main(void);

public:
	WebSocket(const uint prio);


};



#endif /* INC_WEBSOCKET_H_ */
