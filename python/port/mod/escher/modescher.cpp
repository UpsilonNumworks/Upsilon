extern "C"
{
#include "modescher.h"
#include <py/objtuple.h>
#include <py/runtime.h>
}

// #include "apps/apps_container.h"
// #include "apps/global_preferences.h"
#include "port.h"
#include <escher/clipboard.h>

mp_obj_t modescher_set_clipboard(mp_obj_t text)
{
  const char *txt = mp_obj_str_get_str(text);
  Clipboard *clip = Clipboard::sharedClipboard();
  clip->store(txt);
  return mp_const_none;
}