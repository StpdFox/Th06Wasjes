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
#include <fstream>

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
	char buff[256]{0};
	//std::cout << "reading" << std::endl;
	if(readerFifo == -1)
	{
		std::cout << "open" << std::endl;
		readerFifo = open(m_pathRead.c_str(), O_RDONLY);
	}

	int size = read(readerFifo, buff, 256);

	if(size > 0)
	{
		//fgets(buff, 256, fp);
//		std::cout << "line: " << line << std::endl;
		std::cout << "buff: " << buff << std::endl;
		std::string str(buff);
		if(str.find("GETNewWProg") != std::string::npos)
		{
			unsigned i = str.find(",");
			unsigned start = ++i;
			unsigned count = 0;
			while(str[i] != ',')
			{
				++i;
				++count;
			}
			std::string temp = str.substr(start, count);
			std::cout << "temp: " << temp << std::endl;
			std::string rpm = str.substr(++i);
			std::cout << "rpm: " << rpm << std::endl;
			WasProgram wp;
			wp.RPM = atoi(rpm.c_str());
			wp.temp = atoi(temp.c_str());
			wp.timeSpoelen = 600;
			wp.timeWassing = 3000;
			wp.timecentrifugeren = 600;
			m_wbc.setWProg(wp);
		}
		else if(str.find("GET") != std::string::npos)
		{
			std::cout << "get Wrogs" << std::endl;
			m_wbc.getWProgs();
		}
		else if(str.find("Start") != std::string::npos)
		{
			uint i = atoi(&buff[6]);
			std::cout << "Start i:" << i << std::endl;
			if(m_wps.size() >= i)
			{
				WasProgram wp = m_wps[i];
				wp.RPM = calculateRPM(wp.RPM);
				std::cout << "RPM: " << wp.RPM << std::endl;
				m_wbc.startWProg(wp);
			}
		}
	}
}

void WebSocket::writeWashingProgramsToFifo()
{
	std::cout << "send w progs" << std::endl;
	std::string message = "";
	for(const WasProgram &wp : m_wps)
	{
		//message += std::to_string(wp.timeSpoelen) + ',' + std::to_string(wp.timeWassing) + ',' + std::to_string(wp.temp) + ',' +
		//		  std::to_string(wp.timecentrifugeren) + ',' + std::to_string(wp.RPM) + ';';
		message += std::to_string(wp.temp) + ',' + std::to_string(wp.RPM) + ';';

	}
	message += '?';
	//std::cout << message << std::endl;
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
			std::ofstream file;
			file.open("/home/hendrik/Documents/status.txt");
			if(cs.phase == NONE)			file << "Phase Done.";
			if(cs.phase == WASSEN)			file << "Phase Wassen. Time remaining: " << std::to_string(cs.timeRemaining / 60);
			if(cs.phase == SPOELEN)			file << "Phase Spoelen. Time remaining: " << std::to_string(cs.timeRemaining / 60);
			if(cs.phase == CENTRIFUGEREN)	file << "Phase Centrifugeren. Time remaining: " << std::to_string(cs.timeRemaining / 60);
			file.close();
			std::cout << "time remaining" << cs.timeRemaining << std::endl;
		}
		else if(ev == m_wasProgramsFlag)
		{
			m_wps = m_wasProgramsPool.read();
			writeWashingProgramsToFifo();
		}
		else if(ev == m_checkPipe)
		{
			readFifo();
		}
	}
}

uint8_t WebSocket::calculateRPM(const uint RPM)
{
	uint8_t calcRPM = 0.0885 * RPM - 77.714;
	if(calcRPM > 64) return 64;
	else if(calcRPM < 2) return 2;
	else return calcRPM;

}

WebSocket::~WebSocket()
{
	unlink(m_pathWrite.c_str());
	close(readerFifo);
}
