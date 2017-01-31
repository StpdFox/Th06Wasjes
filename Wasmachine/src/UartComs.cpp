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
#include <string.h>

#include "UartComs.h"

UartComs::UartComs()
{
	m_fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
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
    struct termios tty;
    memset (&tty, 0, sizeof tty);

    cfsetospeed (&tty, B9600);
    cfsetispeed (&tty, B9600);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tcsetattr (m_fd, TCSANOW, &tty);

    fcntl(m_fd, F_SETFL, 0);
}

int UartComs::writeUart(const uint8_t command, const uint8_t value)
{
	int n;
	n = write(m_fd, &command, 1);
	n = write(m_fd, &value, 1);
	if(n == -1) return -1;
	//std::cout << "N: " << n << std::endl;
	sleep(0.01);

	//std::cout << "reading" << std::endl;
	char buf[256];
	int byte = read(m_fd, (void*)buf, 255);
	//std::cout << "Byte: " << byte << std::endl;

	if(n == -1) return -1;

	//std::cout << "responds: " << (int)buf[1] << std::endl;
	return (int)buf[1];
}

int UartComs::readUart(const uint8_t request)
{
	int n;
	const uint8_t command = 1;

	n = write(m_fd, &request, 1);
	n = write(m_fd, &command, 1);

	if(n == -1) return -1;

	char buf[256];
	n = read(m_fd, buf, 256);
	if(n == -1) return -1;

	return (int)buf[1];
}

bool UartComs::setRunning()
{
	uint8_t request = 1;
	uint8_t command = 16;

	if(writeUart(request, command) == 4) return true;

	return false;
}

bool UartComs::setIdle()
{
	uint8_t request = 1;
	uint8_t command = 32;

	if(writeUart(request, command) == 2) return true;

	return false;
}

UartComs::~UartComs()
{
	close(m_fd);
}




















