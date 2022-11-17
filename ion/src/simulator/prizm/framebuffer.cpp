#include "framebuffer.h"
#include <ion/display.h>
#include "main.h"

#include <stdio.h>

static KDColor sPixels[Ion::Display::Width * Ion::Display::Height];
static bool sFrameBufferActive = true;

namespace Ion {
namespace Display {

static KDFrameBuffer sFrameBuffer = KDFrameBuffer(sPixels, KDSize(Ion::Display::Width, Ion::Display::Height));

void pushRect(KDRect r, const KDColor * pixels) {
  if (sFrameBufferActive) {
    Simulator::Main::setNeedsRefresh();
    sFrameBuffer.pushRect(r, pixels);
  }
}

void pushRectUniform(KDRect r, KDColor c) {
  if (sFrameBufferActive) {
    Simulator::Main::setNeedsRefresh();
    sFrameBuffer.pushRectUniform(r, c);
  }
}

void pullRect(KDRect r, KDColor * pixels) {
  if (sFrameBufferActive) {
    sFrameBuffer.pullRect(r, pixels);
  }
}

}
}

namespace Ion {
namespace Simulator {
namespace Framebuffer {

const KDColor * address() {
  return sPixels;
}

void setActive(bool enabled) {
  sFrameBufferActive = enabled;
}

void writeToFile(const char * filename) {
  // // Write as a raw RGB565 file
  // FILE * f = fopen(filename, "wb");
  // if (f == NULL) {
  //   return;
  // }
  // for (int i = 0; i < Ion::Display::Width * Ion::Display::Height; i++) {
  //   uint16_t color = sPixels[i];
  //   fwrite(&color, 2, 1, f);
  // }
  // fclose(f);
}

}
}
}