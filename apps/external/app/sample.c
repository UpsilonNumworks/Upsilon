#include <extapp_api.h>

void extapp_main(int argc, char **argv) {
  extapp_pushRectUniform(10, 10, LCD_WIDTH-20, LCD_HEIGHT-20, 0);
  extapp_msleep(1000);
}
