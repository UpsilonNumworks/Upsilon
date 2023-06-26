#ifndef ION_SIMULATOR_MAIN_H
#define ION_SIMULATOR_MAIN_H
#include <stdint.h>

namespace Ion {
namespace Simulator {
namespace Main {

void init();
void quit();

void setNeedsRefresh();
void refresh();

void runPowerOffSafe(void (*powerOffSafeFunction)(), bool prepareVRAM);

enum class CalculatorType : uint8_t {
    Unchecked = (uint8_t)-1,
    Unknown = 0,
    Physical = 1,
    Emulator = 2,
    Other = 3
};

}
}
}

#endif