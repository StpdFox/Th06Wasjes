#include "PassiveIOHandler.h"
#include "PeriodiekeIOHandler.h"
#include "WasProgUitvoerHandler.h"
#include "TempSensor.h"
#include "WaterLevelSensor.h"
#include "WebSocket.h"
#include "WasProBehCntr.h"
#include "UartComs.h"

int main(int argc, char** argv)
{
	UartComs uc;

    TempSensor ts('a', uc);
    WaterLevelSensor wls("\x06", uc);

    PeriodiekeIOHandler perIOHandler(1, 1 S);

    perIOHandler.addEventSource(&ts);
    perIOHandler.addEventSource(&wls);

    WasProgUitvoerHandler wPUH(0, ts, wls, perIOHandler, uc);
    
    //WasProBehCntr WasProgrammaBeheerController(3, wPUH);

    WebSocket ws(4, wPUH);

    RTOS::run();
    
    return 0;
}
