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
//	m_fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
//	if(m_fd == -1)
//	{
//		std::cout << "Unable to open port" << std::endl;
//	}
//	else
//	{
//		std::cout << "Port open" << std::endl;
//		configure();
//	}
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

	tcsetattr(m_fd, TCSANOW, &port_settings);
	fcntl(m_fd, F_SETFL, 1);
}

int UartComs::writeUart(const uint8_t command, const uint8_t value)
{
//	int n;
//	n = write(m_fd, &command, 1);
//	n = write(m_fd, &value, 1);
//	if(n == -1) return -1;
//	std::cout << "N: " << n << std::endl;
//	sleep(0.01);
//
//	std::cout << "reading" << std::endl;
//	char buf[256];
//	int byte = read(m_fd, (void*)buf, 255);
//	std::cout << "Byte: " << byte << std::endl;
//
//	if(n == -1) return -1;
//
//	std::cout << "responds: " << (int)buf[1] << std::endl;
//	return (int)buf[1];

    std::cout << "doing stuff" << std::endl;
    int fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);

    struct termios port_settings;

    cfsetispeed(&port_settings, B9600);
    cfsetospeed(&port_settings, B9600);


    port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
    port_settings.c_cflag &= ~CSTOPB;
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;

    tcsetattr(fd, TCSANOW, &port_settings);

    fcntl(fd, F_SETFL, 10);
    std::cout << "going to write" << std::endl;
    uint8_t request = 1;
    uint8_t command2 = 16;
    char buf[256];
    int byte = 0;

    write(fd, &request, 1);
    std::cout << "going to write" << std::endl;
    write(fd, &command2, 1);

    sleep(0.001);

    byte = read(fd, (void*)buf, 255);
    std::cout << "byte: " << byte << std::endl;
    std::cout << "buf: " << buf << std::endl;
    printf("[0]: %x\n", buf[0]);
    printf("[1]: %x\n", buf[1]);


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




















