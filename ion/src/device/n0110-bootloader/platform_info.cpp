#include <ion.h>
#include <assert.h>
#include "apps/apps_container_storage.h"

#ifndef PATCH_LEVEL
#error This file expects PATCH_LEVEL to be defined
#endif

#ifndef EPSILON_VERSION
#error This file expects EPSILON_VERSION to be defined
#endif

#ifndef OMEGA_VERSION_SHORT
#error This file expects OMEGA_VERSION_SHORT to be defined
#endif

#ifndef UPSILON_VERSION
#error This file expects UPSILON_VERSION to be defined
#endif

extern "C" {
  extern void recovery_start();
  extern void eadk_display_draw_string(const char * text, KDPoint point, bool large_font, KDColor text_color, KDColor background_color);

  #if HOME_DISPLAY_EXTERNALS
  extern uint8_t g_appsContainerStorageRaw[];
  #endif

  extern uint32_t _m_externalAppsFlashStart;
}

namespace Ion {
extern char staticStorageArea[];
}

#if HOME_DISPLAY_EXTERNALS
// Ideally this line should be done in apps_container.cpp to avoid including
// high-level code in Ion (low-level), but GCC consider the value to be invalid
// if referenced between compilations units.
const uint8_t * const externalAppsRAMStart = g_appsContainerStorageRaw + AppsContainerStorage::externalHeapOffset();
const uint8_t * const externalAppsRAMEnd = g_appsContainerStorageRaw + AppsContainerStorage::externalHeapOffset() + Home::App::k_externalHeapSize;
#endif

constexpr void * storageAddress = &(Ion::staticStorageArea);

typedef void (*recoveryStartPointerType)();
constexpr recoveryStartPointerType recoveryStartPointer = &(recovery_start);

typedef void (*drawStringPointerType)(const char * text, KDPoint point, bool large_font, KDColor text_color, KDColor background_color);
constexpr drawStringPointerType drawStringPointer = &(eadk_display_draw_string);

class KernelHeader {
public:
  constexpr KernelHeader() :
    m_header(Magic),
    m_version{EPSILON_VERSION},
    m_patchLevel{PATCH_LEVEL},
    m_footer(Magic) { }
  const char * version() const {
    assert(m_header == Magic);
    assert(m_footer == Magic);
    return m_version;
  }
  const char * patchLevel() const {
    assert(m_header == Magic);
    assert(m_footer == Magic);
    return m_patchLevel;
  }
private:
  constexpr static uint32_t Magic = 0xDEC00DF0;
  uint32_t m_header;
  const char m_version[8];
  const char m_patchLevel[8];
  uint32_t m_footer;
};

const KernelHeader __attribute__((section(".kernel_header"), used)) k_kernelHeader;

// We can't use a constexpr class like KernelHeader due to m_externalAppsRAMStart
// being extern. Ideally we would declare symbols using LD and reference their
// address, but the way the external apps buffer is declared (inside a C++ class)
// prevent declaring a symbol from LD.
// TODO: Restore constexpr version (available in git history)
struct UserlandHeader {
  uint32_t m_header;
  const char m_expectedEpsilonVersion[8];
  void * m_storageAddressRAM;
  size_t m_storageSizeRAM;
  uint32_t * m_externalAppsFlashStart;
  uint32_t m_externalAppsFlashEnd;
  const uint8_t * m_externalAppsRAMStart;
  const uint8_t * m_externalAppsRAMEnd;
  uint32_t m_footer;
  uint32_t m_omegaMagicHeader;
  const char m_omegaVersion[4];
  drawStringPointerType m_drawStringAddress;
  const char m_padding[8];
  const volatile char m_username[16];
  uint32_t m_omegaMagicFooter;
  uint32_t m_upsilonMagicHeader;
  const char m_UpsilonVersion[16];
  uint32_t m_osType;
  uint32_t m_upsilonMagicFooter;
  uint32_t m_upsilonExtraMagicHeader;
  recoveryStartPointerType m_recoveryAddress;
  uint32_t m_extraVersion;
  uint32_t m_upsilonExtraMagicFooter;
};
constexpr static uint32_t Magic = 0xDEC0EDFE;
constexpr static uint32_t OmegaMagic = 0xEFBEADDE;
constexpr static uint32_t UpsilonMagic = 0x55707369;
constexpr static uint32_t OSType = 0x79827178;
constexpr static uint32_t UpsilonExtraMagic = 0xaa7073ff;

const UserlandHeader __attribute__((section(".userland_header"), used)) k_userlandHeader = {
  .m_header = Magic,
  .m_expectedEpsilonVersion = {EPSILON_VERSION},
  .m_storageAddressRAM = storageAddress,
  .m_storageSizeRAM = Ion::Storage::k_storageSize,
  #if HOME_DISPLAY_EXTERNALS
  .m_externalAppsFlashStart = &_m_externalAppsFlashStart,
  .m_externalAppsFlashEnd = 0x907FFFFF,
  .m_externalAppsRAMStart = externalAppsRAMStart,
  .m_externalAppsRAMEnd = externalAppsRAMEnd,
  #else
  .m_externalAppsFlashStart = 0xFFFFFFFF,
  .m_externalAppsFlashEnd = 0xFFFFFFFF,
  .m_externalAppsRAMStart = 0xFFFFFFFF,
  .m_externalAppsRAMEnd = 0xFFFFFFFF,
  #endif
  .m_footer = Magic,
  .m_omegaMagicHeader = OmegaMagic,
  .m_omegaVersion = {OMEGA_VERSION_SHORT},
  .m_drawStringAddress = drawStringPointer,
  .m_padding = {"\0\0\0\0\0\0\0"},
#ifdef OMEGA_USERNAME
  .m_username = {OMEGA_USERNAME},
#else
  .m_username = {"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"},
#endif
  .m_omegaMagicFooter = OmegaMagic,
  .m_upsilonMagicHeader = UpsilonMagic,
  .m_UpsilonVersion = {UPSILON_VERSION},
  .m_osType = OSType,
  .m_upsilonMagicFooter = UpsilonMagic,
  .m_upsilonExtraMagicHeader = UpsilonExtraMagic,
  .m_recoveryAddress = recoveryStartPointer,
  .m_extraVersion = 1,
  .m_upsilonExtraMagicFooter = UpsilonExtraMagic,
};


class SlotInfo {

public:
  SlotInfo() :
    m_header(Magic),
    m_footer(Magic) {}
  void update() {
    m_header = Magic;
    m_kernelHeaderAddress = &k_kernelHeader;
    m_userlandHeaderAddress = &k_userlandHeader;
    m_footer = Magic;
  }

private:
  constexpr static uint32_t Magic = 0xEFEEDBBA;
  uint32_t m_header;
  const KernelHeader * m_kernelHeaderAddress;
  const UserlandHeader * m_userlandHeaderAddress;
  uint32_t m_footer;

};

const char k_omega_version[16] = {OMEGA_VERSION};
const char * Ion::omegaVersion() {
  // We don't use the UserlandHeader, as for NWA compatibility it can only
  // contain the short version and we want the interface to use the full version
  return k_omega_version;
}

const char * Ion::upsilonVersion() {
  return k_userlandHeader.m_UpsilonVersion;
}

const volatile char * Ion::username() {
  return k_userlandHeader.m_username;
}

const char * Ion::softwareVersion() {
  return k_kernelHeader.version();
}

const char * Ion::patchLevel() {
  return k_kernelHeader.patchLevel();
}

const void * Ion::storageAddress() {
  return k_userlandHeader.m_storageAddressRAM;
}

SlotInfo * slotInfo() {
  static SlotInfo __attribute__((used)) __attribute__((section(".slot_info"))) slotInformation;
  return &slotInformation;
}

void Ion::updateSlotInfo() {
  slotInfo()->update();
}

const uint32_t * Ion::externalAppsFlashStart() {
  return k_userlandHeader.m_externalAppsFlashStart;
}
