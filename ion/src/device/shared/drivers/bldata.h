#include <ion.h>

namespace Ion 
{
namespace Device
{
  class BootloaderSharedData {
    public:
      constexpr static uint32_t Magic = 0x626C6461;
      static BootloaderSharedData * sharedBootloaderData();

      BootloaderSharedData();

      void setRecovery(uint32_t address, uint32_t size) { m_storageAddress = address; m_storageSize = size; }
      uint32_t storageAddress() const { return m_storageAddress; }
      uint32_t storageSize() const { return m_storageSize; }
    private:
      uint32_t m_header;
      uint32_t m_storageAddress;
      uint32_t m_storageSize;
      uint32_t m_footer;
  };
}
}
