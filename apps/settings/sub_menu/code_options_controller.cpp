#include "code_options_controller.h"
#include <assert.h>
#include "../../global_preferences.h"
#include "../../apps_container.h"

using namespace Shared;
 
namespace Settings {

CodeOptionsController::CodeOptionsController(Responder * parentResponder) :
  GenericSubController(parentResponder),
  m_preferencesController(this)
{
  m_chevronCellFontSize.setMessageFont(KDFont::LargeFont);
  m_switchCellAutoCompletion.setMessageFont(KDFont::LargeFont);
  m_switchCellSyntaxHighlighting.setMessageFont(KDFont::LargeFont);
  m_switchCellCursorSaving.setMessageFont(KDFont::LargeFont);
  m_gaugeCellPythonHeap.setMessageFont(KDFont::LargeFont);
  this->heap_clicked = false;
  this->heap_level = GlobalPreferences::sharedGlobalPreferences()->getPythonHeap();
  this->last_heap_level = this->heap_level;
}

bool CodeOptionsController::handleEvent(Ion::Events::Event event) {

  // I'm doing this here and not in the switch bc i don't want to handle this with the Right event :)
  if((event == Ion::Events::OK || event == Ion::Events::EXE) && selectedRow() == 3) this->heap_clicked = !this->heap_clicked;
  
  // I'm not using the left and right events bc it is already used to exit the sub menu
  if((event == Ion::Events::Plus || event == Ion::Events::Minus || event == Ion::Events::Left || event == Ion::Events::Right) && selectedRow() == 3)
  {
    if(!GlobalPreferences::sharedGlobalPreferences()->isPythonInit) {
      // If Python is not started yet since the boot we can modify the future heap
      if(event == Ion::Events::Plus || event == Ion::Events::Right) this->heap_level++; else this->heap_level--;
      if(this->heap_level < 1) this->heap_level = 1;
      if(this->heap_level > 21) this->heap_level = 21;
      if(this->heap_level == 1) Container::activeApp()->displayWarning(I18n::Message::PythonToLowHeap);
      GlobalPreferences::sharedGlobalPreferences()->setPythonHeap(this->heap_level);
      m_selectableTableView.reloadCellAtLocation(m_selectableTableView.selectedColumn(), m_selectableTableView.selectedRow());
      AppsContainer::sharedAppsContainer()->redrawWindow(true);
    } else {
      // We can't modify it so we ask to reset the calculator
      Container::activeApp()->displayWarning(I18n::Message::PythonHeapPythonAlreadyStarted1, I18n::Message::PythonHeapPythonAlreadyStarted2);
    }
    return true;
  }
  if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
    switch (selectedRow()){
      case 1:
        GlobalPreferences::sharedGlobalPreferences()->setAutocomplete(!GlobalPreferences::sharedGlobalPreferences()->autocomplete());
        m_selectableTableView.reloadCellAtLocation(m_selectableTableView.selectedColumn(), m_selectableTableView.selectedRow());
        break;
      case 3:
        m_selectableTableView.reloadCellAtLocation(m_selectableTableView.selectedColumn(), m_selectableTableView.selectedRow());
        break;
      case 2:
        GlobalPreferences::sharedGlobalPreferences()->setSyntaxhighlighting(!GlobalPreferences::sharedGlobalPreferences()->syntaxhighlighting());
        m_selectableTableView.reloadCellAtLocation(m_selectableTableView.selectedColumn(), m_selectableTableView.selectedRow());
        break;
      case 4:
        GlobalPreferences::sharedGlobalPreferences()->setCursorSaving(!GlobalPreferences::sharedGlobalPreferences()->cursorSaving());
        m_selectableTableView.reloadCellAtLocation(m_selectableTableView.selectedColumn(), m_selectableTableView.selectedRow());
        break;
      case 5:
        m_selectableTableView.reloadCellAtLocation(m_selectableTableView.selectedColumn(), m_selectableTableView.selectedRow());
        break;
      default:
        GenericSubController * subController = nullptr;
        subController = &m_preferencesController;
        subController->setMessageTreeModel(m_messageTreeModel->childAtIndex(selectedRow()));
        StackViewController * stack = stackController();
        m_lastSelect = selectedRow();
        stack->push(subController);
        break;
    }
    AppsContainer::sharedAppsContainer()->redrawWindow(true);
    return true;
  }
  AppsContainer::sharedAppsContainer()->redrawWindow(true);
  return GenericSubController::handleEvent(event);
}

HighlightCell * CodeOptionsController::reusableCell(int index, int type) {
  assert(type == 0);
  assert(index >= 0 && index < k_totalNumberOfCell);
  if (index == 0) {
    return &m_chevronCellFontSize;
  }
  else if (index == 1) {
    return &m_switchCellAutoCompletion;
  }
  else if (index == 2) {
    return &m_switchCellSyntaxHighlighting;
  }
  else if (index == 3) {
    return &m_gaugeCellPythonHeap;
    
  }
  else return &m_switchCellCursorSaving; 
}

int CodeOptionsController::reusableCellCount(int type) {
  assert(type == 0);
  return k_totalNumberOfCell;
}

void CodeOptionsController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  GenericSubController::willDisplayCellForIndex(cell, index);

  I18n::Message thisLabel = m_messageTreeModel->childAtIndex(index)->label();

  if (thisLabel == I18n::Message::FontSizes){
    MessageTableCellWithChevronAndMessage * myTextCell = (MessageTableCellWithChevronAndMessage *)cell;
    myTextCell->setMessage(thisLabel);
    GlobalPreferences::sharedGlobalPreferences()->font() == KDFont::LargeFont
        ? myTextCell->setSubtitle(I18n::Message::LargeFont)
        : myTextCell->setSubtitle(I18n::Message::SmallFont);
  }
#ifdef HAS_CODE
  else if (thisLabel == I18n::Message::Autocomplete) {
    MessageTableCellWithSwitch * mySwitchCell = (MessageTableCellWithSwitch *)cell;
    SwitchView * mySwitch = (SwitchView *)mySwitchCell->accessoryView();
    mySwitch->setState(GlobalPreferences::sharedGlobalPreferences()->autocomplete());
  }
  else if (thisLabel == I18n::Message::SyntaxHighlighting) {
    MessageTableCellWithSwitch * mySwitchCell = (MessageTableCellWithSwitch *)cell;
    SwitchView * mySwitch = (SwitchView *)mySwitchCell->accessoryView();
    mySwitch->setState(GlobalPreferences::sharedGlobalPreferences()->syntaxhighlighting());
  }
  else if (thisLabel == I18n::Message::CursorSaving) {
    MessageTableCellWithSwitch * mySwitchCell = (MessageTableCellWithSwitch *)cell;
    SwitchView * mySwitch = (SwitchView *)mySwitchCell->accessoryView();
    mySwitch->setState(GlobalPreferences::sharedGlobalPreferences()->cursorSaving());
  }
#endif

  if(index == 3)
  {
    MessageTableCellWithGauge *gaugeCell = (MessageTableCellWithGauge*)cell;
    GaugeView * myGauge = (GaugeView *)gaugeCell->accessoryView();
    myGauge->setLevel(this->heap_level / 20.00);
    gaugeCell->setMessage(I18n::Message::About);
    if(!this->heap_clicked) {
      gaugeCell->setMessageFont(KDFont::LargeFont);
      gaugeCell->setMessage(I18n::Message::PythonHeap);
    }
    else {
      gaugeCell->setMessageFont(KDFont::SmallFont);
      gaugeCell->setMessage(I18n::Message::PythonHeapExplanation);
    }
    
  }
}

}