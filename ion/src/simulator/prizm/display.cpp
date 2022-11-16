#include "display.h"
#include "framebuffer.h"
#include "kandinsky/color.h"
#include <cstdint>
#include <ion/display.h>
#include <string.h>

#include <stdio.h>

namespace Ion {
namespace Simulator {
namespace Display {

void init() {
  // lcd_init(SCR_320x240_565);
}

void quit() {
  // lcd_init(SCR_TYPE_INVALID);
}

static int draw_count = 0;

void draw() {
  // TODO: dupdate here

  /* static const bool has_colors_cache = has_colors;

  if (has_colors_cache) {
    // same as lcd_blit((void*)Framebuffer::address(), SCR_320x240_565)
    memcpy(REAL_SCREEN_BASE_ADDRESS, (void*)Framebuffer::address(), 320 * 240 * sizeof(uint16_t));
  } else {  // invert screen color if running on classic
    for (unsigned int i = 0; i < 320 * 240; i++) {
      reinterpret_cast<uint16_t*>(REAL_SCREEN_BASE_ADDRESS)[i] = 0xFFFF - Framebuffer::address()[i];
    }
  } */

  // printf("draw\n");
  draw_count++;

  if (draw_count == 60) {
    printf("draw_count == 60\n");

    const KDColor* pixels = Framebuffer::address();
    // Loop over all the pixels excluding the status bar
    // It is 18 pixels high
    // Add all their values to a counter as some kind of hash
    uint64_t hash = 0;
    for (int y = 18; y < 240; y++) {
      for (int x = 0; x < 320; x++) {
        hash += pixels[y * 320 + x];
      }
    }
    printf("hash: %lu\n", hash);

    Framebuffer::writeToFile("test.bin");
  }
}

}
}
}
