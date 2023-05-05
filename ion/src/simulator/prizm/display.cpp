#include "display.h"
#include "framebuffer.h"
#include "kandinsky/color.h"
#include <cstdint>
#include <gint/display-cg.h>
#include <ion/display.h>
#include <string.h>

#include <stdio.h>

#include <gint/display.h>
#include <gint/keyboard.h>

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
  // if (draw_count == 0) {
  //   dclear(C_RED);
  //   dupdate();
  // }
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

  // Loop over all the pixels and plot them
  // for (int x = 0; x < Ion::Display::Width; x++) {
  //   for (int y = 0; y < /* Ion::Display::Height */ 224; y++) {
  //     // Get the color of the pixel
  //     KDColor color = Framebuffer::address()[x + y * Ion::Display::Width];
  //     // Plot the pixel
  //     dpixel(x, y, color);
  //   }
  // }
  // dupdate();

  // Faster implementation: Use memcpy to copy each line to gint_vram
  // for (int y = 0; y < /* Ion::Display::Height */ 224; y++) {
  //   memcpy(gint_vram + (y * 396), Framebuffer::address() + y * Ion::Display::Width, Ion::Display::Width * sizeof(uint16_t));
  // }
  dupdate();

  // printf("draw\n");
  // draw_count++;

  // if (draw_count == 10) {
  //   // printf("draw_count == 10\n");
  //   dclear(C_GREEN);
  //   dtext(1, 16, C_BLACK, "draw_count == 10");

  //   const KDColor* pixels = Framebuffer::address();
  //   // Loop over all the pixels excluding the status bar
  //   // It is 18 pixels high
  //   // Add all their values to a counter as some kind of hash
  //   uint64_t hash = 0;
  //   for (int y = 18; y < 240; y++) {
  //     for (int x = 0; x < 320; x++) {
  //       hash += pixels[y * 320 + x];
  //     }
  //   }
  //   // printf("hash: %lu\n", hash);
  //   if (hash == 4352844898) {
  //     // printf("SUCCESS\n");
  //     dtext(1, 32, C_BLACK, "SUCCESS");
  //   } else {
  //     // printf("FAILURE\n");
  //     dtext(1, 32, C_BLACK, "FAILURE");
  //   }

  //   dupdate();
  //   while (true) {
  //     getkey();
  //   }

  //   // Framebuffer::writeToFile("test.bin");
  // }
}

}
}
}
