/*
 * Logger.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: hendrik
 */

#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>

#include <iostream>

#include "Logger.h"

Logger::Logger(const uint prio) :
	task(prio, "Logger"),
	m_logChannel(this, "LogChannel")
{
	auto now = std::chrono::system_clock::now();
	auto time =  std::chrono::system_clock::to_time_t(now);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&time), "%Y%m%d%H%M%S");
	m_fileName = "LogFile" + ss.str();
}

void Logger::write(const std::string &message)
{
	//TODO turn on to for logging
	//m_logChannel.write(message);
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
