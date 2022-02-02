#include <ion/keyboard.h>
#include <libndls.h>
#include <n2DLib.h>

#include "keyboard.h"
#include "main.h"

using namespace Ion::Keyboard;

class KeyPair {
public:
  constexpr KeyPair(Key key, t_key ndlessKey) :
    m_key(key),
    m_ndlessKey(ndlessKey)
  {}
  Key key() const { return m_key; }
  t_key ndlessKey() const { return m_ndlessKey; }
private:
  Key m_key;
  t_key m_ndlessKey;
};

constexpr static KeyPair sKeyPairs[] = {
  KeyPair(Key::Down,             KEY_NSPIRE_DOWN),
  KeyPair(Key::Up,               KEY_NSPIRE_UP),
  KeyPair(Key::Left,             KEY_NSPIRE_LEFT),
  KeyPair(Key::Right,            KEY_NSPIRE_RIGHT),
  KeyPair(Key::Shift,            KEY_NSPIRE_SHIFT),
  KeyPair(Key::EXE,              KEY_NSPIRE_ENTER),
  KeyPair(Key::EXE,              KEY_NSPIRE_RET),
  KeyPair(Key::Back,             KEY_NSPIRE_ESC),
  KeyPair(Key::Toolbox,          KEY_NSPIRE_TAB),
  KeyPair(Key::Backspace,        KEY_NSPIRE_DEL),
  KeyPair(Key::Home,             KEY_NSPIRE_HOME),
  KeyPair(Key::OK,               KEY_NSPIRE_CLICK),
  KeyPair(Key::One,              KEY_NSPIRE_1),
  KeyPair(Key::Two,              KEY_NSPIRE_2),
  KeyPair(Key::Three,            KEY_NSPIRE_3),
  KeyPair(Key::Four,             KEY_NSPIRE_4),
  KeyPair(Key::Five,             KEY_NSPIRE_5),
  KeyPair(Key::Six,              KEY_NSPIRE_6),
  KeyPair(Key::Seven,            KEY_NSPIRE_7),
  KeyPair(Key::Eight,            KEY_NSPIRE_8),
  KeyPair(Key::Nine,             KEY_NSPIRE_9),
  KeyPair(Key::Zero,             KEY_NSPIRE_0),
  KeyPair(Key::Dot,              KEY_NSPIRE_PERIOD),
  KeyPair(Key::LeftParenthesis,  KEY_NSPIRE_LP),
  KeyPair(Key::RightParenthesis, KEY_NSPIRE_RP),
  KeyPair(Key::Square,           KEY_NSPIRE_SQU),
  KeyPair(Key::Exp,              KEY_NSPIRE_eEXP),
  KeyPair(Key::Power,            KEY_NSPIRE_EXP),
  KeyPair(Key::Comma,            KEY_NSPIRE_COMMA),
  KeyPair(Key::Pi,               KEY_NSPIRE_PI),
  KeyPair(Key::Multiplication,   KEY_NSPIRE_MULTIPLY),
  KeyPair(Key::Division,         KEY_NSPIRE_DIVIDE),
  KeyPair(Key::Plus,             KEY_NSPIRE_PLUS),
  KeyPair(Key::Minus,            KEY_NSPIRE_MINUS),
  KeyPair(Key::EE,               KEY_NSPIRE_EE),
  KeyPair(Key::Shift,            KEY_NSPIRE_SHIFT),
  KeyPair(Key::Alpha,            KEY_NSPIRE_CTRL),
  KeyPair(Key::Var,              KEY_NSPIRE_VAR)
};

constexpr int sNumberOfKeyPairs = sizeof(sKeyPairs)/sizeof(KeyPair);

namespace Ion {
namespace Keyboard {

static bool getTPArrow(t_key* result) {
  touchpad_report_t tpReport;

  result->row = result->tpad_row = _KEY_DUMMY_ROW;
	result->col = result->tpad_col = _KEY_DUMMY_COL;
	result->tpad_arrow = TPAD_ARROW_NONE;
  
  if (!touchpad_scan(&tpReport)) {
    //result->tpad_arrow = (tpad_arrow_t)tpReport.arrow;
    // nasty workaround for n2DLib isKey()
    switch (tpReport.arrow) {
      case TPAD_ARROW_UP:
        *result = KEY_NSPIRE_UP;
        break;
      case TPAD_ARROW_DOWN:
        *result = KEY_NSPIRE_DOWN;
        break;
      case TPAD_ARROW_LEFT:
        *result = KEY_NSPIRE_LEFT;
        break;
      case TPAD_ARROW_RIGHT:
        *result = KEY_NSPIRE_RIGHT;
        break;
      case TPAD_ARROW_CLICK:
        *result = KEY_NSPIRE_CLICK;
        break;
      default:
        return 0;
    }
    return 1;
  } else
      return 0;
}

State scan() {
  State state;
  t_key result;
  
  // Grab this opportunity to refresh the display if needed
  Simulator::Main::refresh();
  
  // Catch the physical keyboard events
  if (get_key_pressed(&result) || getTPArrow(&result)) {
    for (int i = 0; i < sNumberOfKeyPairs; i++) {
      if (isKey(result, sKeyPairs[i].ndlessKey())) {
        state.setKey(sKeyPairs[i].key());
	    }
    }
  } else {
    if (on_key_pressed()) {
      state.setKey(Key::OnOff);
    }
  }

  return state;
}

}
}

namespace Ion {
namespace Simulator {
namespace Keyboard {

bool scanHandlesKey(t_key key) {
  for (int i = 0; i < sNumberOfKeyPairs; i++) {
    if (isKey(key, sKeyPairs[i].ndlessKey())) {
      return true;
    }
  }
  return false;
}

}
}
}
