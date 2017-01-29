#ifndef __WasProgrammaUitvoerenController
#define __WasProgrammaUitvoerenController

#include "WasProgramPhase.h"
#include "PassiveIOHandler.h"
#include "PeriodiekeIOHandler.h"
#include "Logger.h"

class WasProgUitvoerHandler;
class UartComs;

class WasProgrammaUitvoerenController
{
private:
    WasProgUitvoerHandler &m_wPUH;
    PeriodiekeIOHandler &m_perIOHandler;
    PassiveIOHandler m_pasIOHandler;
    Logger m_logger;
    
    WasProgramPhase m_currentPhase;
    int m_currentTemp = -1;
    uint m_wLevel = 0;
    uint m_targetWLevel = 10;
    bool m_moterLeft = false;
    bool m_heaterOn = false;
    bool m_waterValveOpen = false;
    bool m_pumpOn = false;
    uint8_t m_currentRPM = 0;
    
    bool m_perIOHandSuspend = true;

    bool m_changeMoter = true;
    bool m_spinLeft = false;

    Phase m_lastPhase = NONE;
    bool m_doneWithLastPhase = true;

    void clearPhase();
public:
    WasProgrammaUitvoerenController(WasProgUitvoerHandler &wPUH, PeriodiekeIOHandler &perIOHandler, UartComs &uc);
    void setNewPhase(const WasProgramPhase &wProgPhase);
    void setNewTemp(const uint);
    void setNewWLvl(const uint);
    void timeOver();
    void checkWasMachine();
};

#endif
