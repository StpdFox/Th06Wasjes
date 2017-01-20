#include <iostream>
#include "PassiveIOHandler.h"

PassiveIOHandler::PassiveIOHandler(const uint prio, UartComs &uc) :
    task(prio, "PassIOHandler"),
	m_uc(uc),
    m_doorLockFlag(this, "DoorLockFlag"),
    m_doorUnlockFlag(this, "DoorUnLockFlag"),
    m_heaterOnFlag(this, "HeaterOnFlag"),
    m_heaterOffFlag(this, "HeaterOffFlag"),
    m_waterValveOpenFlag(this, "WaterValveOpenFlag"),
    m_waterValveCloseFlag(this, "WaterValveCloseFlag"),
    m_signalLedOnFlag(this, "SignalLedOnFlag"),
    m_signalLedOffFlag(this, "SignalLedOffFlag"),
    m_pumpOnFlag(this, "PumpOnFlag"),
    m_pumpOffFlag(this, "PumpOffFlag"),
    m_newRPMFlag(this, "NewRPMFlag"),
    m_motorRPMPool("MotorRPMPool"),
    m_doorLock(DefaultOutput(2, 64, 128)),
    m_heater(DefaultOutput(7, 16, 32)),
    m_waterValve(DefaultOutput(3, 16, 32)),
    m_signalLed(DefaultOutput(11, 16, 32)),
    m_pump(DefaultOutput(5, 16, 32)),
    m_motor(Motor(10))
{
m_uc.writeUart("\x01", "\x10");
}

void PassiveIOHandler::lockDoor()
{
   set(m_doorLockFlag);
}

void PassiveIOHandler::unlockDoor()
{
    set(m_doorUnlockFlag);
}

void PassiveIOHandler::heaterOn()
{
    set(m_heaterOnFlag);
}

void PassiveIOHandler::heaterOff()
{
    set(m_heaterOffFlag);
}

void PassiveIOHandler::openWaterValve()
{
    //std::cout << "set flag" << std::endl;
    //set(m_waterValveOpenFlag);
    m_waterValveOpenFlag.set();
}

void PassiveIOHandler::closeWaterValve()
{
    set(m_waterValveCloseFlag);
}

void PassiveIOHandler::signalLedOn()
{
    set(m_signalLedOnFlag);
}

void PassiveIOHandler::signalLedOff()
{
    set(m_signalLedOffFlag);
}

void PassiveIOHandler::setMotoRPM(const int RPM)
{
    m_motorRPMPool.write(RPM);
    set(m_newRPMFlag);
}

void PassiveIOHandler::pumpOn()
{
    set(m_pumpOnFlag);
}

void PassiveIOHandler::pumpOff()
{
    set(m_pumpOffFlag);
}

void PassiveIOHandler::main(void)
{
	while(true)
	{
		RTOS::event ev = wait(m_doorLockFlag + m_doorUnlockFlag + m_heaterOnFlag + m_heaterOffFlag + m_waterValveOpenFlag + m_waterValveCloseFlag +
							  m_signalLedOnFlag + m_signalLedOffFlag + m_pumpOnFlag + m_pumpOffFlag + m_newRPMFlag);

		if(ev == m_doorLockFlag)
		{
			std::cout << "Door locked" << std::endl;
		}
		else if(ev == m_doorUnlockFlag)
		{
			std::cout << "Door unlocked" << std::endl;
		}
		else if(ev == m_heaterOnFlag)
		{
			 std::cout << "Heater on" << std::endl;
		}
		else if(ev == m_heaterOffFlag)
		{
			std::cout << "Heater off" << std::endl;
		}
		else if(ev == m_waterValveOpenFlag)
		{
			m_uc.writeUart("\x03", "\x10");
			std::cout << "Water valve open" << std::endl;
			sleep (1 S);
			std::cout << m_uc.readUart("\x06") << std::endl;
		}
		else if(ev == m_waterValveCloseFlag)
		{
			m_uc.writeUart("\x03", "\x20");
			std::cout << "Water valve closed" << std::endl;
		}
		else if(ev == m_signalLedOnFlag)
		{
			std::cout << "Signal led on" << std::endl;
		}
		else if(ev == m_signalLedOffFlag)
		{
			std::cout << "Signal led off" << std::endl;
		}
		else if(ev == m_pumpOnFlag)
		{
			std::cout << "Pump on" << std::endl;
		}
		else if(ev == m_pumpOffFlag)
		{
			std::cout << "Pump off" << std::endl;
		}
		else if(ev == m_newRPMFlag)
		{
			m_uc.writeUart("\x0A", "\x05");
			std::cout << "set new RPM: " << m_motorRPMPool.read() << std::endl;
			if(m_motorRPMPool.read() < 0)
			{
				m_uc.writeUart("\x0A", "\x02");
			}
			else
			{
				m_uc.writeUart("\x0A", "\x50");
			}
		}
	}
}

PassiveIOHandler::~PassiveIOHandler()
{}

























