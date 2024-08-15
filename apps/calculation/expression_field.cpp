#include "expression_field.h"
#include <poincare/symbol.h>
#include <poincare/horizontal_layout.h>
#include <poincare/code_point_layout.h>

using namespace Poincare;
namespace Calculation {

bool ExpressionField::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Back) {
    return false;
  }
  if (event == Ion::Events::Ans) {
    handleEventWithText(Poincare::Symbol::k_ans);
    return true;
  }
  if (isEditing() && isEmpty() &&
      (event == Ion::Events::Multiplication ||
       event == Ion::Events::Plus ||
       event == Ion::Events::Power ||
       event == Ion::Events::Square ||
       event == Ion::Events::Division ||
       event == Ion::Events::Sto ||
       event == Ion::Events::EE)) {
    handleEventWithText(Poincare::Symbol::k_ans);
  }
  if (event == Ion::Events::Minus
      && isEditing()
      && fieldHasOnlyAMinus()) {
    setText(Poincare::Symbol::k_ans);
  }
  return (::ExpressionField::handleEvent(event));
}

bool ExpressionField::fieldHasOnlyAMinus() const {
  if (editionIsInTextField()) {
        const char *inputBuffer = m_textField.draftTextBuffer();
        return (inputBuffer[0] == '-' && inputBuffer[1] == '\0');
    } 
    Layout layout = m_layoutField.layout();
    if (layout.type() == LayoutNode::Type::HorizontalLayout && layout.numberOfChildren() == 1) {
        Layout child = layout.childAtIndex(0);
        if (child.type() == LayoutNode::Type::CodePointLayout) {
            CodePointLayout &codePointLayout = static_cast<CodePointLayout &>(child);
            if (codePointLayout.codePoint() == '-'){
            return true;
            }
        }
    }
    return false;
}

}
