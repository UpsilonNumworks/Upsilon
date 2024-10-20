#include "bldata.h"
#include <ion.h>
#include <new>

namespace Ion {
  uint32_t staticSharedData[sizeof(Ion::Device::BootloaderSharedData)/sizeof(uint32_t)] __attribute__((section(".bootloader_shared"))) __attribute__((used)) = {0};

  Device::BootloaderSharedData * Device::BootloaderSharedData::sharedBootloaderData() {
    static BootloaderSharedData * sharedData = new (staticSharedData) BootloaderSharedData();
    return sharedData;
  }

  Device::BootloaderSharedData::BootloaderSharedData() {
    if (m_header != Magic || m_footer != Magic) {
      m_header = Magic;
      m_storageAddress = 0;
      m_storageSize = 0;
      m_footer = Magic;
   }
  }
}
