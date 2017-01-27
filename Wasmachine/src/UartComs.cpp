/*
 * UartComs.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: hendrik
 */

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "UartComs.h"

UartComs::UartComs()
{
	m_fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
	fcntl(m_fd, F_SETFL, 1);
	if(m_fd == -1)
	{
		std::cout << "Unable to open port" << std::endl;
	}
	else
	{
		std::cout << "Port open" << std::endl;
		configure();
	}
}

void UartComs::configure()
{
	struct termios port_settings;

	cfsetispeed(&port_settings, B9600);
	cfsetospeed(&port_settings, B9600);


	port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;
//
//	tcsetattr(m_fd, TCSANOW, &port_settings);
}

void UartComs::writeUart(const char *command, const char *value)
{
	int n;
	n = write(m_fd, command, 1);
	n = write(m_fd, value, 1);
	if(n == -1) std::cout << "Unable to write" << std::endl;
//	else
//	{
//		char buf[256];
//		n = read(m_fd, buf, 256);
//		if(n == -1) std::cout << "Unable to read" << std::endl;
//		std::cout << "buf: " << buf << std::endl;
//	}
}

int UartComs::readUart(const uint8_t &request)
{
	int n;
	const uint8_t command = 1;

	n = write(m_fd, &request, 1);
	n = write(m_fd, &command, 1);

	if(n == -1)
	{
		std::cout << "Unable to write" << std::endl;
		return -1;
	}
	else
	{
		char buf[256];
		n = read(m_fd, (void*)buf, 255);
		if(n == -1)
		{
			std::cout << "Unable to read" << std::endl;
			return -1;
		}
		else
		{
			std::cout << "0: " << (int)buf[0] << std::endl;
			std::cout << "1: " << (int)buf[1] << std::endl;
			//std::cout << "bytes: " << n << std::endl;
			return (int)buf[1];
		}
	}
}

int UartComs::readUart()
{
	std::cout << "read Uart" << std::endl;

	char buf[256];
	int byte = read(m_fd, (void*)buf, 255);

	std::cout << "0: " << (int)buf[0] << std::endl;
	std::cout << "1: " << (int)buf[1] << std::endl;

	return (int)buf[1];
}

UartComs::~UartComs()
{

}
