#include "main.h"
#include "display.h"
#include "platform.h"

#include <cstddef>
#include <gint/display-cg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <ion.h>
#include <ion/events.h>

extern "C" {
int main() {
  Ion::Simulator::Main::init();
  ion_main(0, NULL);
  Ion::Simulator::Main::quit();

  return 0;
}
}

namespace Ion {
namespace Simulator {
namespace Main {

static bool sNeedsRefresh = false;

void init() {
  Ion::Simulator::Display::init();
  setNeedsRefresh();
}

void setNeedsRefresh() {
  sNeedsRefresh = true;
}

void refresh() {
  if (!sNeedsRefresh) {
    return;
  }

  Display::draw();

  sNeedsRefresh = false;
}

void quit() {
  Ion::Simulator::Display::quit();
}

}
}
}
