#include "usb_protection_controller.h"

#include <apps/i18n.h>
#include <apps/settings/main_controller.h>
#include <assert.h>
#include <ion/storage.h>
#include <poincare/preferences.h>
#include "../../apps_container.h"
#include "../../global_preferences.h"

using namespace Poincare;
using namespace Shared;

namespace Settings {

UsbInfoController::UsbInfoController(Responder *parentResponder) :
        GenericSubController(parentResponder),
        m_usbProtectionLevelController(this),
        m_contentView(&m_selectableTableView) {
  m_switchCell.setMessageFont(KDFont::LargeFont);
  m_dfuLevelCell.setMessageFont(KDFont::LargeFont);
}

bool UsbInfoController::handleEvent(Ion::Events::Event event) {
  if ((Ion::Events::OK == event || Ion::Events::EXE == event) && selectedRow() == 0) {
    if (!GlobalPreferences::sharedGlobalPreferences()->dfuUnlocked()) {
      if (!GlobalPreferences::sharedGlobalPreferences()->isInExamMode()) {
        Ion::LED::setColor(KDColorPurple);
        Ion::LED::setBlinking(500, 0.5f);
      }
      GlobalPreferences::sharedGlobalPreferences()->setDfuUnlocked(true);
    } else {
      if (!GlobalPreferences::sharedGlobalPreferences()->isInExamMode()) {
        Ion::LED::setColor(KDColorBlack);
      }
      GlobalPreferences::sharedGlobalPreferences()->setDfuUnlocked(false);
    }
    m_selectableTableView.reloadCellAtLocation(0, 0);
    return true;
  }

  if ((Ion::Events::OK == event || Ion::Events::EXE == event) && selectedRow() == 1) {
    GenericSubController *subController = &m_usbProtectionLevelController;
    subController->setMessageTreeModel(m_messageTreeModel->childAtIndex(1));
    StackViewController *stack = stackController();
    m_lastSelect = selectedRow();
    stack->push(subController);
    return true;
  }

  // We cannot use things like willExitResponderChain because this view can disappear due to an USB connection,
  // and in this case we must keep the DFU status.
  if ((event != Ion::Events::USBPlug && event != Ion::Events::USBEnumeration) &&
      GlobalPreferences::sharedGlobalPreferences()->dfuUnlocked()) {
    GlobalPreferences::sharedGlobalPreferences()->setDfuUnlocked(false);
    m_selectableTableView.reloadCellAtLocation(0, 0);
    Container::activeApp()->displayWarning(I18n::Message::USBProtectionReactivated);
    if (!GlobalPreferences::sharedGlobalPreferences()->isInExamMode()) {
      Ion::LED::setColor(KDColorBlack);
    }
    return true;
  }

  return GenericSubController::handleEvent(event);
}

HighlightCell *UsbInfoController::reusableCell(int index, int type) {
  if (index == 0) {
    return &m_switchCell;
  }
  assert(index == 1);
  return &m_dfuLevelCell;
}

int UsbInfoController::reusableCellCount(int type) {
  assert(type == 0);
  return 2;
}

void UsbInfoController::willDisplayCellForIndex(HighlightCell *cell, int index) {
  GenericSubController::willDisplayCellForIndex(cell, index);

  if (index == 0) {
    MessageTableCellWithSwitch *myCell = (MessageTableCellWithSwitch *)cell;
    SwitchView *mySwitch = (SwitchView *)myCell->accessoryView();
    mySwitch->setState(!GlobalPreferences::sharedGlobalPreferences()->dfuUnlocked());
  } else if (index == 1) {
    MessageTableCellWithChevronAndMessage *mcell = (MessageTableCellWithChevronAndMessage *)cell;
    int currentLevel = GlobalPreferences::sharedGlobalPreferences()->dfuLevel();
    if (currentLevel == 0) {
      mcell->setSubtitle(I18n::Message::USBDefaultLevelDesc);
    } else if (currentLevel == 1) { ;
      mcell->setSubtitle(I18n::Message::USBLowLevelDesc);
    } else {
      assert(currentLevel == 2);
      mcell->setSubtitle(I18n::Message::USBParanoidLevelDesc);
    }
  }
}

void UsbInfoController::didEnterResponderChain(Responder *previousFirstResponder) {
  m_contentView.reload();
  I18n::Message infoMessages[] = {I18n::Message::USBExplanation1, I18n::Message::USBExplanation2,
                                  I18n::Message::USBExplanation3};
  m_contentView.setMessages(infoMessages, k_numberOfExplanationMessages);
}
}  
