#include "main.h"
#include "keyboard.h"
#include "platform.h"
//#include "driver/common.h"
// #include <libndls.h>
// #include <n2DLib.h>
#include "events.h"
#include <assert.h>
#include <ion/events.h>
#include <string.h>

// class AlphaKeyPair {
//   public:
//     constexpr AlphaKeyPair(char key, char shiftAlphaKey, t_key ndlessKey) :
//       m_key(key),
//       m_shiftAlphaKey(shiftAlphaKey),
//       m_ndlessKey(ndlessKey)
//     {}
//     char key() const { return m_key; }
//     char shiftAlphaKey() const { return m_shiftAlphaKey; }
//     t_key ndlessKey() const { return m_ndlessKey; }

//   private:
//     char m_key;
//     char m_shiftAlphaKey;
//     t_key m_ndlessKey;
// // };

// constexpr static AlphaKeyPair aKeyPairs[] = {
//   AlphaKeyPair('a', 'A', KEY_NSPIRE_A),
//   AlphaKeyPair('b', 'B', KEY_NSPIRE_B),
//   AlphaKeyPair('c', 'C', KEY_NSPIRE_C),
//   AlphaKeyPair('d', 'D', KEY_NSPIRE_D),
//   AlphaKeyPair('e', 'E', KEY_NSPIRE_E),
//   AlphaKeyPair('f', 'F', KEY_NSPIRE_F),
//   AlphaKeyPair('g', 'G', KEY_NSPIRE_G),
//   AlphaKeyPair('h', 'H', KEY_NSPIRE_H),
//   AlphaKeyPair('i', 'I', KEY_NSPIRE_I),
//   AlphaKeyPair('j', 'J', KEY_NSPIRE_J),
//   AlphaKeyPair('k', 'K', KEY_NSPIRE_K),
//   AlphaKeyPair('l', 'L', KEY_NSPIRE_L),
//   AlphaKeyPair('m', 'M', KEY_NSPIRE_M),
//   AlphaKeyPair('n', 'N', KEY_NSPIRE_N),
//   AlphaKeyPair('o', 'O', KEY_NSPIRE_O),
//   AlphaKeyPair('p', 'P', KEY_NSPIRE_P),
//   AlphaKeyPair('q', 'Q', KEY_NSPIRE_Q),
//   AlphaKeyPair('r', 'R', KEY_NSPIRE_R),
//   AlphaKeyPair('s', 'S', KEY_NSPIRE_S),
//   AlphaKeyPair('t', 'T', KEY_NSPIRE_T),
//   AlphaKeyPair('u', 'U', KEY_NSPIRE_U),
//   AlphaKeyPair('v', 'V', KEY_NSPIRE_V),
//   AlphaKeyPair('w', 'W', KEY_NSPIRE_W),
//   AlphaKeyPair('x', 'X', KEY_NSPIRE_X),
//   AlphaKeyPair('y', 'Y', KEY_NSPIRE_Y),
//   AlphaKeyPair('z', 'Z', KEY_NSPIRE_Z),
//   AlphaKeyPair(' ', ' ', KEY_NSPIRE_SPACE)
// };

// constexpr int aNumberOfKeyPairs = sizeof(aKeyPairs)/sizeof(AlphaKeyPair);

namespace Ion {
namespace Events {


Event getPlatformEvent() {
  Event result = None;
  // t_key scanResult;
  // static t_key prevScanResult = {_KEY_DUMMY_ROW, _KEY_DUMMY_COL, _KEY_DUMMY_ROW, _KEY_DUMMY_COL, TPAD_ARROW_NONE};
  // static bool keyDown = false;

  // bool getKeyResult = get_key_pressed(&scanResult);

  // if (getKeyResult) {

  //   if (isKey(scanResult, KEY_NSPIRE_SCRATCHPAD)) {  // 'Quit' bound to 'Scratchpad'
  //     return Termination;
  //   }

  //   if (!isKey(scanResult, prevScanResult)) {
  //     keyDown = false;
  //     prevScanResult = scanResult;
  //   }

  //   if (!keyDown && !Simulator::Keyboard::scanHandlesKey(scanResult)) {  // handle alphabetical keypad press
  //     keyDown = true;
  //     for (int i = 0; i < aNumberOfKeyPairs; i++) {
  //       if (isKey(scanResult, aKeyPairs[i].ndlessKey())) {
  //         //strlcpy(sharedExternalTextBuffer(), aKeyPairs[i].key(), sharedExternalTextBufferSize);
  //         if (Ion::Events::isShiftActive() && Ion::Events::isAlphaActive()) {
  //           sharedExternalTextBuffer()[0] = aKeyPairs[i].shiftAlphaKey();
  //           if (!Ion::Events::isLockActive()) Ion::Events::removeShift();
  //         } else {
  //           sharedExternalTextBuffer()[0] = aKeyPairs[i].key();
  //         }
  //         sharedExternalTextBuffer()[1] = '\0';
  //         return ExternalText;
  //       }
  //     }
  //   }

  // } else keyDown = false;

  return result;
}


}
}
