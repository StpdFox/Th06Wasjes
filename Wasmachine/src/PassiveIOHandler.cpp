#include <iostream>
#include "PassiveIOHandler.h"
#include "WasProgUitvoerHandler.h"
#include <fcntl.h>

PassiveIOHandler::PassiveIOHandler(const uint prio, UartComs &uc, WasProgUitvoerHandler &wuh) :
    task(prio, "PassIOHandler"),
	m_uc(uc),
	m_wuh(wuh),
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
    m_doorLock(DefaultOutput(2, 64, 128, uc)),
    m_heater(DefaultOutput(7, 16, 32, uc)),
    m_waterValve(DefaultOutput(3, 16, 32, uc)),
    m_signalLed(DefaultOutput(11, 16, 32, uc)),
    m_pump(DefaultOutput(5, 16, 32, uc)),
    m_motor(Motor(10, uc))
{
//	if(m_uc.setRunning() == false) std::cerr << "Not running!" << std::endl;
//	else							std::cout << "running!" << std::endl;
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

void PassiveIOHandler::setMotoRPM(const uint8_t RPM)
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
			if(m_uc.writeUart(2, 1) == 1)
			{
				m_wuh.setErrorFlag();
				m_signalLed.on();
				m_uc.setIdle();
			}
			else
			{
				m_uc.setRunning();
				if(m_doorLock.on()) std::cout << "Door locked" << std::endl;
				else				std::cerr << "Door not locked!" << std::endl;
			}
		}
		else if(ev == m_doorUnlockFlag)
		{
			m_uc.setIdle();
			if(m_doorLock.off()) std::cout << "Door unlocked" << std::endl;
			else				std::cerr << "Door not unlocked!" << std::endl;
		}
		else if(ev == m_heaterOnFlag)
		{
			if(m_heater.on()) std::cout << "Heater on" << std::endl;
			else				std::cerr << "Heater not on" << std::endl;
		}
		else if(ev == m_heaterOffFlag)
		{
			if(m_heater.off()) std::cout << "Heater off" << std::endl;
			else				std::cerr << "Heater not off" << std::endl;
		}
		else if(ev == m_waterValveOpenFlag)
		{
			if(m_waterValve.on()) std::cout << "Water valve open" << std::endl;
			else				std::cerr << "Water valve not open" << std::endl;
		}
		else if(ev == m_waterValveCloseFlag)
		{
			if(m_waterValve.off()) std::cout << "Water valve closed" << std::endl;
			else				std::cerr << "Water valve not closed" << std::endl;
		}
		else if(ev == m_signalLedOnFlag)
		{
			if(m_signalLed.on()) std::cout << "Signal led on" << std::endl;
			else				std::cerr << "Signal led not on" << std::endl;
		}
		else if(ev == m_signalLedOffFlag)
		{
			if(m_signalLed.off()) std::cout << "Signal led off" << std::endl;
			else				std::cerr << "Signal led not off" << std::endl;
		}
		else if(ev == m_pumpOnFlag)
		{
			if(m_pump.on()) std::cout << "Pump on" << std::endl;
			else				std::cerr << "Pump not on" << std::endl;
		}
		else if(ev == m_pumpOffFlag)
		{
			if(m_pump.off()) std::cout << "Pump off" << std::endl;
			else				std::cerr << "Pump not off" << std::endl;
		}
		else if(ev == m_newRPMFlag)
		{
			if(m_motor.setRPM(m_motorRPMPool.read())) std::cout << "Motor set" << std::endl;
			else				  std::cerr << "Motor not set" << std::endl;
		}
	}
}

PassiveIOHandler::~PassiveIOHandler()
{}

























