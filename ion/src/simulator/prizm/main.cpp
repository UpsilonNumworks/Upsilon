#include "main.h"
#include "display.h"
#include "platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <ion.h>
#include <ion/events.h>
// #include <n2DLib.h>
// #include <libndls.h>

//#include "driver/common.h"

int main(int argc, char * argv[]) {
  printf("Hello, world!\n");

  Ion::Simulator::Main::init();

  // std::vector<const char *> arguments(argv, argv + argc);

  // const char * language = "en";
  // if (language != nullptr) {
  //   arguments.push_back("--language");
  //   arguments.push_back(language);
  // }

  // ion_main(arguments.size(), &arguments[0]);
  ion_main(argc, argv);
  Ion::Simulator::Main::quit();

  return 0;
}

namespace Ion {
namespace Simulator {
namespace Main {

static bool sNeedsRefresh = false;

void init() {
  //Ion::Simulator::CommonDriver::init();
  Ion::Simulator::Display::init();
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
  Ion::Simulator::Display::quit();
}

}
}
}

