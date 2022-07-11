#ifndef BOOTLOADER_SLOTS_SLOT_H
#define BOOTLOADER_SLOTS_SLOT_H

#include <stdint.h>
#include "kernel_header.h"
#include "userland_header.h"

namespace Bootloader {

enum class SlotType {
  Raw,
  Epsilon,
  Omega,
  Upsilon,
  Khi,
};

class Slot {

public:
  Slot(uint32_t address) :
    m_kernelHeader(reinterpret_cast<KernelHeader*>(address)),
    m_userlandHeader(reinterpret_cast<UserlandHeader*>(address + 64 * 1024)),
    m_address(address) { }

  const KernelHeader* kernelHeader() const;
  const UserlandHeader* userlandHeader() const;
  const uint32_t address() const { return m_address; }
  virtual SlotType type() const { return SlotType::Raw; }

  [[ noreturn ]] void boot() const;

  bool valid() const {
    return m_kernelHeader->isValid() && m_userlandHeader->isValid();
  }

protected:
  const KernelHeader* m_kernelHeader;
  const UserlandHeader* m_userlandHeader;
  const uint32_t m_address;

};

}

#endif