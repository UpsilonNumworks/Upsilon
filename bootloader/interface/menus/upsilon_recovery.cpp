#include "upsilon_recovery.h"
#include <bootloader/slots/slot.h>
#include <bootloader/usb_data.h>
#include <ion/src/device/shared/drivers/board.h>
#include <ion.h>
#include <stdlib.h>

extern "C" void jump_to_firmware(const uint32_t* stackPtr, const void(*startPtr)(void));

Bootloader::UpsilonRecoveryMenu::UpsilonRecoveryMenu() : Menu(KDColorBlack, KDColorWhite, Messages::upsilonRecoveryTitle, Messages::mainTitle) {
    setup();
}

void Bootloader::UpsilonRecoveryMenu::setup() {
  m_defaultColumns[0] = Column(Messages::upsilonRecoveryMessage1, k_small_font, 0, true);
  m_defaultColumns[1] = Column(Messages::upsilonRecoveryMessage2, k_small_font, 0, true);
  m_defaultColumns[2] = Column(Messages::upsilonRecoveryMessage3, k_small_font, 0, true);
  m_defaultColumns[3] = Column(Messages::upsilonRecoveryMessage4, k_small_font, 0, true);
  m_defaultColumns[4] = Column(Messages::upsilonRecoveryMessage5, k_small_font, 0, true);
  
  m_columns[0] = ColumnBinder(&m_defaultColumns[0]);
  m_columns[1] = ColumnBinder(&m_defaultColumns[1]);
  m_columns[2] = ColumnBinder(&m_defaultColumns[2]);
  m_columns[3] = ColumnBinder(&m_defaultColumns[3]);
  m_columns[4] = ColumnBinder(&m_defaultColumns[4]);
}

void Bootloader::UpsilonRecoveryMenu::postOpen() {
  // We override the open method
  for (;;) {
    uint64_t scan = Ion::Keyboard::scan();
    if (scan == Ion::Keyboard::State(Ion::Keyboard::Key::Back)) {
      while (Ion::Keyboard::scan() == Ion::Keyboard::State(Ion::Keyboard::Key::Back));
      forceExit();
      return;
    } else if (scan == Ion::Keyboard::State(Ion::Keyboard::Key::OnOff)) {
      Ion::Power::suspend();
      return;
    } else if (scan == Ion::Keyboard::State(Ion::Keyboard::Key::OK)) {
      Slot slot = Slot::Upsilon();
      Ion::Device::Board::bootloaderMPU();
      // Deinitialize the backlight to prevent bugs when the firmware boots 
      Ion::Backlight::shutdown();
      jump_to_firmware(slot.kernelHeader()->stackPointer(), slot.userlandHeader()->upsilonRecoveryBootFunction());
      for(;;);
    }
  }
}
