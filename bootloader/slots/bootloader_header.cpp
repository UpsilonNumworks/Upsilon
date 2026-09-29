#include <ion.h>

namespace Ion {
namespace Device {


class BootloaderHeader {
public:
  constexpr BootloaderHeader() :
    m_header(BootloaderMagic),
    m_bootloader_version(0xFFFFFFFF),
    m_footer(BootloaderMagic) {}
private:
  constexpr static uint32_t BootloaderMagic = 0xDEC0B007;

  uint32_t m_header;
  uint32_t m_bootloader_version;
  uint32_t m_footer;
};

const BootloaderHeader __attribute__((section(".header"), used)) bootloader_header;

}
}
