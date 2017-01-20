/*
 * UartComs.h
 *
 *  Created on: Jan 20, 2017
 *      Author: hendrik
 */

#ifndef INC_UARTCOMS_H_
#define INC_UARTCOMS_H_


class UartComs
{
private:
	int m_fd;

	void configure();
public:
	UartComs();
	~UartComs();

	void writeUart(const char *command, const char *value);
	int readUart(const char *command);
};



#endif /* INC_UARTCOMS_H_ */
