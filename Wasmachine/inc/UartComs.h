/*
 * UartComs.h
 *
 *  Created on: Jan 20, 2017
 *      Author: hendrik
 */

#ifndef INC_UARTCOMS_H_
#define INC_UARTCOMS_H_

#include <iostream>

class UartComs
{
private:


	void configure();
public:
	UartComs();
	~UartComs();

	int m_fd;

	int writeUart(const uint8_t command, const uint8_t value);
	int readUart(const uint8_t command);
	bool setRunning();
	bool setIdle();
};



#endif /* INC_UARTCOMS_H_ */
