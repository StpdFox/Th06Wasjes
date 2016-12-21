#include "PassiveIOHandler.h"
#include "PeriodiekeIOHandler.h"
#include "WasProgUitvoerHandler.h"
#include "TempSensor.h"
#include "WaterLevelSensor.h"

int main(int argc, char** argv)
{
    TempSensor ts('a');
    WaterLevelSensor wls('a');
    
    PeriodiekeIOHandler perIOHandler(1, 1000000);
    
    perIOHandler.addEventSource(&ts);
    perIOHandler.addEventSource(&wls);
    
    //PassiveIOHandler blijft hangen op een wait, terwijl wasPorgUitvoerHandler er geen last van heeft
    PassiveIOHandler pasIOHandler(2);
    
    std::cout << "PassiveIOHandler adress: " << &pasIOHandler << std::endl;
    WasProgUitvoerHandler wPUH(0, ts, wls, pasIOHandler);
    
    RTOS::run();
    
    return 0;
}