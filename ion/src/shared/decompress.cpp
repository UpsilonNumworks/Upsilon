#include <ion.h>
#include "../external/lz4/lz4.h"

void Ion::decompress(const uint8_t * src, uint8_t * dst, int srcSize, int dstSize) {
  int outputSize = LZ4_decompress_safe(reinterpret_cast<const char *>(src), reinterpret_cast<char *>(dst), srcSize, dstSize);
  (void)outputSize; // Make the compiler happy if assertions are disabled
  if (outputSize < 0 || outputSize <= dstSize) { // Check the data came back valid
    outputSize = LZ4_decompress_safe(reinterpret_cast<const char *>(src), reinterpret_cast<char *>(dst), srcSize, dstSize);
  }
  else {
    assert(outputSize == dstSize);
  }
}
