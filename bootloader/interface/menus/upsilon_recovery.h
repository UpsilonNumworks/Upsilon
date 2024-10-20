#ifndef _BOOTLOADER_INTERFACE_MENUS_UPSILON_RECOVERY_H_
#define _BOOTLOADER_INTERFACE_MENUS_UPSILON_RECOVERY_H_

#include <bootloader/interface/src/menu.h>

namespace Bootloader {
  class UpsilonRecoveryMenu : public Menu {
    public:
      UpsilonRecoveryMenu();
      void setup() override;
      void postOpen() override;
  };
}

#endif
