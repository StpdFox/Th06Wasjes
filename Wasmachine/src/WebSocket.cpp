/*
 * WebSocket.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#include "WebSocket.h"
#include "WasProgram.h"

WebSocket::WebSocket(const uint prio, WasProBehCntr &wbc) :
    task(prio, "WebSocket"),
    m_wbc(wbc)
{}

void WebSocket::main(void)
{
	uint time = 1;
	while(true)
	{
		std::cout << "WebSocket sleep" << std::endl;
		sleep(time S);
		std::cout << "WebSocket a wake" << std::endl;
		WasProgram wp;
		wp.temp = 25;
		wp.timeWassing = 10;
		std::cout << "WebSocket setting stuff" << std::endl;
		m_wbc.startWprog(wp);
		//std::cout << "WebSocket suspend" << std::endl;
		time = 10000000;
		//suspend();
	}
}
