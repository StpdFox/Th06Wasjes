#include "PassiveIOHandler.h"
#include "PeriodiekeIOHandler.h"
#include "WasProgUitvoerHandler.h"
#include "TempSensor.h"
#include "WaterLevelSensor.h"

int main(int argc, char** argv)
{
    TempSensor ts('a');
    WaterLevelSensor wls('a');
    
    PeriodiekeIOHandler perIOHandler(2, 1000000);
    
    perIOHandler.addEventSource(&ts);
    perIOHandler.addEventSource(&wls);
    
    //PassiveIOHandler blijft hangen op een wait, terwijl wasPorgUitvoerHandler er geen last van heeft
    PassiveIOHandler pasIOHandler(0);
    WasProgUitvoerHandler wPUH(1, ts, wls, pasIOHandler);
    
    RTOS::run();
    
    return 0;
}