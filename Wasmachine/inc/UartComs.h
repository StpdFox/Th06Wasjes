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

	void writeUart(const char *command, const char *value);
	int readUart(const uint8_t &command);
	int readUart();
};



#endif /* INC_UARTCOMS_H_ */
