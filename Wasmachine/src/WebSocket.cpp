/*
 * WebSocket.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WebSocket.h"
#include "WasProgram.h"

WebSocket::WebSocket(const uint prio, WasProgUitvoerHandler &wpUC) :
    task(prio, "WebSocket"),
    m_wbc(3, wpUC, *this),
	m_wasProgramsFlag(this, "wasProgramsFlag"),
	m_progresFlag(this, "ProgresFlag"),
	m_wasProgramsPool("WasProgramsPool"),
	m_progresPool("ProgresPool")
{}

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

void WebSocket::main(void)
{
///	uint time = 1;
	while(true)
	{
//		sleep(time S);
		m_wbc.getWProgs();
		RTOS::event ev = wait(m_wasProgramsFlag + m_progresFlag);
		if(ev == m_progresFlag)
		{
			CurrentStatus cs = m_progresPool.read();
			std::cout << "Time remaining: " << cs.timeRemaining << std::endl;
		}
		else if(ev == m_wasProgramsFlag)
		{
			m_wps = m_wasProgramsPool.read();
			if(m_wps.size() >= 1)
			{
				m_wbc.startWProg(m_wps[0]);
			}
		}

//		WasProgram wp;
//		wp.temp = 25;
//		wp.timeWassing = 60;
//		wp.timeSpoelen = 30;
//		wp.timecentrifugeren = 40;
//		m_wbc.startWProg(wp);
		//std::cout << "WebSocket suspend" << std::endl;
//		time = 10000000;
		//suspend();
	}
}
