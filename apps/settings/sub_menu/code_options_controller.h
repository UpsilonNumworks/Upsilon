#ifndef SETTINGS_CODE_OPTIONS_CONTROLLER_H
#define SETTINGS_CODE_OPTIONS_CONTROLLER_H

#include "generic_sub_controller.h"
#include "preferences_controller.h"
#include "selectable_view_with_messages.h"

namespace Settings {

class CodeOptionsController : public GenericSubController {
public:
  CodeOptionsController(Responder * parentResponder);
  bool handleEvent(Ion::Events::Event event) override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
private:
  constexpr static int k_totalNumberOfCell = 5;
  PreferencesController m_preferencesController;
  MessageTableCellWithChevronAndMessage m_chevronCellFontSize;
  MessageTableCellWithSwitch m_switchCellAutoCompletion;
  MessageTableCellWithSwitch m_switchCellSyntaxHighlighting;
  MessageTableCellWithSwitch m_switchCellCursorSaving;
  MessageTableCellWithGauge m_gaugeCellPythonHeap;
  bool heap_clicked;
  int8_t heap_level;
  int8_t last_heap_level;
};
}

#endif
