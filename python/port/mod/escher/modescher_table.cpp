extern "C"
{
#include "modescher.h"
}

#include <ion.h>

/* We cannot use C99-style struct initialization in C++. As a result, we cannot
 * use the macros that micropython recommends, and we have to hand build those
 * structs. To avoid errors, we drop in a few static_asserts. */

static_assert(sizeof(mp_fun_1_t) == sizeof(mp_fun_0_t), "modescher_table badly formed");
static_assert(sizeof(mp_obj_fun_builtin_fixed_t) == sizeof(mp_obj_base_t) + sizeof(mp_fun_1_t), "modescher_keyboard_keydown_obj badly formed");

const mp_obj_fun_builtin_fixed_t modescher_set_clipboard_obj = {
    {&mp_type_fun_builtin_1},
    {(mp_fun_0_t)modescher_set_clipboard}};

const mp_obj_fun_builtin_fixed_t modescher_get_clipboard_obj = {
    {&mp_type_fun_builtin_0},
    {(mp_fun_0_t)modescher_get_clipboard}};

extern "C" const mp_rom_map_elem_t modescher_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR_set_clipboard), MP_ROM_PTR(&modescher_set_clipboard_obj)},
    {MP_ROM_QSTR(MP_QSTR_get_clipboard), MP_ROM_PTR(&modescher_get_clipboard_obj)}};

STATIC MP_DEFINE_CONST_DICT(modescher_module_globals, modescher_module_globals_table);

static_assert(sizeof(mp_obj_module_t) == sizeof(mp_obj_base_t) + sizeof(mp_obj_dict_t *), "modescher_module badly formed");

extern "C" const mp_obj_module_t modescher_module = {
    {&mp_type_module},
    (mp_obj_dict_t *)&modescher_module_globals,
};
