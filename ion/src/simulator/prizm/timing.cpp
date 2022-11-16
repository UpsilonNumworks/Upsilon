#include <ion/timing.h>
#include "main.h"
// #include <chrono>
// #include <libndls.h>

// static auto start = std::chrono::steady_clock::now();

namespace Ion {
namespace Timing {

uint64_t millis() {
  // auto elapsed = std::chrono::steady_clock::now() - start;
  // return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

  // Dummy implementation
  return 0;
}

void msleep(uint32_t ms) {
  // ::msleep(ms);
}

}
}