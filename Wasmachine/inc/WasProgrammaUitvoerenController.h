#include "WasProgramPhase.h"
#include "PassiveIOHandler.h"
#include "PeriodiekeIOHandler.h"

class WasProgUitvoerHandler;

class WasProgrammaUitvoerenController
{
private:
    PassiveIOHandler &m_pasIOHandler;
    WasProgUitvoerHandler &m_wPUH;
    PeriodiekeIOHandler &m_perIOHandler;
    
    WasProgramPhase m_currentPhase;
    int m_currentTemp = -1;
    uint m_wLevel = 0;
    uint m_targetWLevel = 10;
    bool m_moterLeft = false;
    bool m_heaterOn = false;
    bool m_waterValveOpen = false;
    int m_currentRPM = 0;

    bool m_perIOHandSuspend = true;
    
public:
    WasProgrammaUitvoerenController(PassiveIOHandler &pIOHandler, WasProgUitvoerHandler &wPUH, PeriodiekeIOHandler &perIOHandler);
    void setNewPhase(const WasProgramPhase &wProgPhase);
    void setNewTemp(const uint);
    void setNewWLvl(const uint);
    void checkWasMachine();
};
