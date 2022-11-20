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
// #include <n2DLib.h>
// #include <libndls.h>

#include <gint/display.h>
#include <gint/keyboard.h>

//#include "driver/common.h"

extern "C" {
int main() {
  // printf("Hello, world!\n");
  dclear(C_WHITE);
  Ion::Simulator::Main::init();
  ion_main(0, NULL);

  dtext(1, 32, C_BLACK, "Simulator done!");
  dupdate();
  getkey();

  Ion::Simulator::Main::quit();

  return 0;
}
}

namespace Ion {
namespace Simulator {
namespace Main {

static bool sNeedsRefresh = false;

void init() {
              //Ion::Simulator::CommonDriver::init();
  // Ion::Simulator::Display::init();
              // relayout(); TODO: I assume this was part of Ndless?
}

void relayout() {
  int windowWidth = 320;
  int windowHeight = 240;

  // Keep original aspect ration in screen_only mode.
  /*
  float scale = (float)(Ion::Display::Width) / (float)(Ion::Display::Height);
  if ((float)(windowHeight) * scale > float(windowWidth)) {
    sScreenRect.w = windowWidth;
    sScreenRect.h = (int)((float)(windowWidth) / scale);
  } else {
    sScreenRect.w = (int)((float)(windowHeight) * scale);
    sScreenRect.h = windowHeight;
  }
  sScreenRect.x = (windowWidth - sScreenRect.w) / 2;
  sScreenRect.y = (windowHeight - sScreenRect.h) / 2;
  */

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
                //Ion::Simulator::CommonDriver::deinit();
  // Ion::Simulator::Display::quit();
}

}
}
}

// #include <gint/display.h>
// #include <gint/keyboard.h>

// int main(void)
// {
//   dclear(C_WHITE);
//   dtext(1, 1, C_BLACK, "Sample fxSDK add-in.");
//   dupdate();

//   getkey();
//   return 1;
// }
