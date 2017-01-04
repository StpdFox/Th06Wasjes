/*
 * WebSocket.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

 #include "WebSocket.h"

WebSocket::WebSocket(const uint prio, WasProBehCntr &wbc) :
    task(prio, "WebSocket"),
    m_wbc(wbc)
{}

void WebSocket::main(void)
{
    
}
