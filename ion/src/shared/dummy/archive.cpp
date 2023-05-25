#include "apps/global_preferences.h"
#include <ion/external.h>

#include <stdlib.h>
#include <string.h>

namespace Ion {
namespace External {
namespace Archive {

size_t numberOfFiles() {
  File dummy{};
  size_t count = 0;

  for (count = 0; fileAtIndex(count, dummy); count++) {;}

  return count;
}

int indexFromName(const char *name) {
  File entry{};

  for (int i = 0; fileAtIndex(i, entry); i++) {
    if (entry.readable && strcmp(name, entry.name) == 0) {
      return i;
    }
  }

  return -1;
}

bool executableAtIndex(size_t index, File &entry) {
  File dummy{};
  size_t count = 0;
  size_t final_count = 0;

  for (count = 0; fileAtIndex(count, dummy); count++) {
    if (dummy.isExecutable) {
      if (final_count == index) {
        entry.name = dummy.name;
        entry.data = dummy.data;
        entry.dataLength = dummy.dataLength;
        entry.isExecutable = dummy.isExecutable;
        entry.readable = dummy.readable;
        return true;
      }
      final_count++;
    }
  }
  return false;
}

size_t numberOfExecutables() {
  if (!GlobalPreferences::sharedGlobalPreferences()->externalAppShown()) {
    return 0U;
  }
  File dummy{};
  size_t count = 0;
  size_t final_count = 0;

  for (count = 0; fileAtIndex(count, dummy); count++) {
    if (dummy.isExecutable) {
      final_count++;
    }
  }

  return final_count;
}


bool fileAtIndex(size_t index, File &entry) {
  if (index != 0) {
    return false;
  }

  entry.name = "Built-in";
  entry.data = nullptr;
  entry.dataLength = 0;
  entry.isExecutable = true;
  entry.readable = true;
  return true;
}

extern "C" void extapp_main(void);

uint32_t executeFile(const char * name, void * heap, const uint32_t heapSize) {
  extapp_main();
  return 0;
}

}
}
}
