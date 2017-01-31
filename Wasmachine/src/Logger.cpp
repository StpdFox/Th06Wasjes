/*
 * Logger.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: hendrik
 */

#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>

#include <iostream>

#include "Logger.h"

Logger::Logger(const uint prio) :
	task(prio, "Logger"),
	m_logChannel(this, "LogChannel"),
	m_fileName("Log")
{
	std::ofstream ofs;
	ofs.open(m_fileName, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void Logger::write(const std::string &message)
{
	m_logChannel.write(message);
}

void Logger::main(void)
{
	std::string newMessage;
	std::fstream file;
	while(true)
	{
		newMessage = m_logChannel.read();
		file.open(m_fileName, std::fstream::out | std::fstream::app);
		file << newMessage << '\n';
		file.close();
	}
}

Logger::~Logger()
{}
