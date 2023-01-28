#include <py/obj.h>

mp_obj_t modion_keyboard_keydown(mp_obj_t key_o);
mp_obj_t modion_battery();
mp_obj_t modion_battery_level();
mp_obj_t modion_battery_ischarging();
mp_obj_t modion_get_keys();
mp_obj_t modion_set_brightness(mp_obj_t brightness_mp);
mp_obj_t modion_get_brightness();
mp_obj_t modion_set_dfu(mp_obj_t b);
mp_obj_t modion_set_led_color(mp_obj_t r, mp_obj_t g, mp_obj_t b);
extern const mp_obj_type_t file_type;
