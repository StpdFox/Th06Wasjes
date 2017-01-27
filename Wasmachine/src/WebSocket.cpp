/*
 * WebSocket.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "WebSocket.h"
#include "WasProgram.h"

WebSocket::WebSocket(const uint prio, WasProgUitvoerHandler &wpUC) :
    task(prio, "WebSocket"),
    m_wbc(3, wpUC, *this),
	m_wasProgramsFlag(this, "wasProgramsFlag"),
	m_progresFlag(this, "ProgresFlag"),
	m_wasProgramsPool("WasProgramsPool"),
	m_progresPool("ProgresPool"),
	m_checkPipe(this, 500 MS, "checkPipe")
{
	mkfifo(m_pathWrite.c_str(), 0666);
}

void WebSocket::setWashPrograms(const std::vector<WasProgram> &wps)
{
	m_wasProgramsPool.write(wps);
	m_wasProgramsFlag.set();
}

void WebSocket::setProgres(const CurrentStatus &cs)
{
	m_progresPool.write(cs);
	m_progresFlag.set();
}

void WebSocket::readFifo()
{
	std::cout << "check pipe" << std::endl;
	char buff[1024];

	if(readerFifo == -1)
	{
		std::cout << "open" << std::endl;
		readerFifo = open(m_pathRead.c_str(), O_RDONLY);
	}
	std::cout << "read" << std::endl;
	int size = read(readerFifo, buff, 1024);
	if(size > 0)
	{
		std::cout << "buff: " << buff << std::endl;
		if(strcmp(buff, "GET") == 0)
		{
			std::cout << "get Wrogs" << std::endl;
			m_wbc.getWProgs();
		}
	}
	std::cout << "done checking pipe" << std::endl;
}

void WebSocket::writeWashingProgramsToFifo()
{
	std::cout << "send w progs" << std::endl;
	std::string message = "";
	for(const WasProgram &wp : m_wps)
	{
		message += std::to_string(wp.timeSpoelen) + ',' + std::to_string(wp.timeWassing) + ',' + std::to_string(wp.temp) + ',' +
				  std::to_string(wp.timecentrifugeren) + ',' + std::to_string(wp.RPM) + ';';

	}
	std::cout << message << std::endl;
	int fd;
	int byte;

	fd = open(m_pathWrite.c_str(), O_WRONLY);
	byte = write(fd, message.c_str(), message.size());
	std::cout << "write done" << std::endl;
	(void)byte;
	close(fd);
	std::cout << message << std::endl;
}

void WebSocket::main(void)
{
	//m_wbc.getWProgs();
	while(true)
	{
		RTOS::event ev = wait(m_wasProgramsFlag + m_progresFlag + m_checkPipe);
		if(ev == m_progresFlag)
		{
			CurrentStatus cs = m_progresPool.read();
			std::cout << "Time remaining: " << cs.timeRemaining << std::endl;
		}
		else if(ev == m_wasProgramsFlag)
		{
			m_wps = m_wasProgramsPool.read();
			writeWashingProgramsToFifo();
			if(m_wps.size() >= 1)
			{
				m_wbc.startWProg(m_wps[0]);
			}
		}
		else if(ev == m_checkPipe)
		{
			readFifo();
		}
	}
}

WebSocket::~WebSocket()
{
	unlink(m_pathWrite.c_str());
	close(readerFifo);
}
