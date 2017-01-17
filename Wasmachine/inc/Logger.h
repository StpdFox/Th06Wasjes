/*
 * Logger.h
 *
 *  Created on: Jan 17, 2017
 *      Author: hendrik
 */

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#include <sys/types.h>

#include "pRTOS.h"

class Logger : public RTOS::task
{
private:
	std::string m_fileName;
	RTOS::channel<std::string, 10> m_logChannel;

	void main(void);
public:
	Logger(const uint prio);
	virtual ~Logger();

	void write(const std::string &message);
};



#endif /* INC_LOGGER_H_ */
