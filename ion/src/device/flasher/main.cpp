#include "../shared/usb/calculator.h"
#include "display.h"
#include <ion.h>
#include <ion/src/device/shared/drivers/flash.h>

void ion_main(int argc, const char * const argv[]) {
  // Initialize the backlight
  Ion::Backlight::init();
  // Initialize Flasher display
  Flasher::Display::init();

  // Disable Write Protection
  Ion::Device::Flash::DisableInternalProtection();
  Ion::Device::Flash::SetInternalSectorProtection(0, false);
  Ion::Device::Flash::SetInternalSectorProtection(1,  false);
  Ion::Device::Flash::SetInternalSectorProtection(2, false);
  Ion::Device::Flash::SetInternalSectorProtection(3, false);
  Ion::Device::Flash::EnableInternalProtection();

  while (true) {
    Ion::USB::enable();
    while (!Ion::USB::isEnumerated()) {
    }
    Ion::USB::DFU(false);
  }
}
