#include "integer_list_controller.h"
#include <poincare/based_integer.h>
#include <poincare/integer.h>
#include <poincare/empty_layout.h>
#include <poincare/factor.h>
#include "../app.h"
#include "../../shared/poincare_helpers.h"
#include "poincare/decimal.h"
#include "apps/apps_container.h"
#include "poincare/layout_helper.h"

using namespace Poincare;
using namespace Shared;

namespace Calculation {

Integer::Base baseAtIndex(int index) {
  switch (index) {
    case 0:
      return Integer::Base::Decimal;
    case 1:
      return Integer::Base::Hexadecimal;
    default:
      assert(index == 2);
      return Integer::Base::Binary;
  }
}

void IntegerListController::setExpression(Poincare::Expression e) {
  ExpressionsListController::setExpression(e);
  static_assert(k_maxNumberOfRows >= k_indexOfFactorExpression + 1, "k_maxNumberOfRows must be greater than k_indexOfFactorExpression");
  assert(!m_expression.isUninitialized() && m_expression.type() == ExpressionNode::Type::BasedInteger);
  Integer integer = static_cast<BasedInteger &>(m_expression).integer();
  for (int index = 0; index < k_indexOfFactorExpression - 1; ++index) {
    m_layouts[index] = integer.createLayout(baseAtIndex(index));
  }

  const int * value = (int *)integer.digits();
  int shift = GlobalPreferences::sharedGlobalPreferences()->getDecimalShift();
  m_exponent = (int)log10(abs(*value));

  Decimal decimal = Decimal::Builder(integer, m_exponent);

  char buffer[Poincare::DecimalNode::k_maxBufferSize];
  int numberOfChars = decimal.serialize(buffer, Poincare::DecimalNode::k_maxBufferSize, Preferences::PrintFloatMode::Scientific);

  if (*(UTF8Helper::CodePointSearch(buffer, Ion::InternalStorage::k_dotChar)) != 0) {
    int originalNumber = numberOfChars;
    int maxShift = originalNumber - 3 - (int)log10(abs(m_exponent)) - 1 - 2;
    if (shift > maxShift) {
      shift = maxShift;
      GlobalPreferences::sharedGlobalPreferences()->setDecimalShift(maxShift);
    }
    decimal = Decimal::Builder(integer, m_exponent-shift);
    numberOfChars = decimal.serialize(buffer, Poincare::DecimalNode::k_maxBufferSize, Preferences::PrintFloatMode::Scientific);

    for (int i = 0; i < shift; i++) {
      char c = buffer[i+1];
      buffer[i+1] = buffer[i+2];
      buffer[i+2] = c;
    }

    if (m_exponent - shift == 0) {
      buffer[numberOfChars-1] = '\0';
    }

    if (shift == maxShift && m_exponent - shift != 0) {
      strlcpy(&buffer[shift + 1], &buffer[shift + 2], strlen(&buffer[shift + 1]));
    }
  }

  Layout layout = LayoutHelper::String(buffer, numberOfChars);

  m_layouts[k_indexOfFactorExpression - 1] = layout;
  // Computing factorExpression
  Expression factor = Factor::Builder(m_expression.clone());
  PoincareHelpers::Simplify(&factor, App::app()->localContext(), ExpressionNode::ReductionTarget::User);
  if (!factor.isUndefined()) {
    m_layouts[k_indexOfFactorExpression] = PoincareHelpers::CreateLayout(factor);
  }
}

I18n::Message IntegerListController::messageAtIndex(int index) {
  switch (index) {
    case 0:
      return I18n::Message::DecimalBase;
    case 1:
      return I18n::Message::HexadecimalBase;
    case 2:
      return I18n::Message::BinaryBase;
    case 3:
        return I18n::Message::Scientific;
    default:
      return I18n::Message::PrimeFactors;
  }
}

  bool IntegerListController::handleEvent(Ion::Events::Event event) {
    if (m_listController.selectableTableView()->selectedRow() == 3) {
      int decimalShift = GlobalPreferences::sharedGlobalPreferences()->getDecimalShift();
      if (event == Ion::Events::Left) {
        if (decimalShift > 0 && Preferences::sharedPreferences()->displayMode() != Preferences::PrintFloatMode::Engineering) {
          GlobalPreferences::sharedGlobalPreferences()->setDecimalShift(decimalShift - 1);
          refreshScientificDisplay();
        } else if (decimalShift > 3 && Preferences::sharedPreferences()->displayMode() == Preferences::PrintFloatMode::Engineering) {
          GlobalPreferences::sharedGlobalPreferences()->setDecimalShift(decimalShift - 3);
          refreshScientificDisplay();
        }
        return true;
      } else if (event == Ion::Events::Right) {
        if (Preferences::sharedPreferences()->displayMode() == Preferences::PrintFloatMode::Engineering && m_exponent - decimalShift - 3 >= 0) {
          GlobalPreferences::sharedGlobalPreferences()->setDecimalShift(decimalShift + 3);
        } else if (m_exponent - decimalShift - 1 >= 0) {
          GlobalPreferences::sharedGlobalPreferences()->setDecimalShift(decimalShift + 1);
        }
        refreshScientificDisplay();
        return true;
      }
    }
    return ListController::handleEvent(event);
  }

    void IntegerListController::refreshScientificDisplay() {
      Expression e = m_expression;
      Container::activeApp()->dismissModalViewController();
      setExpression(e);
      Container::activeApp()->displayModalViewController(this, 0.f, 0.f, Metric::CommonTopMargin, Metric::PopUpLeftMargin, 0, Metric::PopUpRightMargin);
      m_listController.selectableTableView()->selectCellAtLocation(0, 3);
    }

}
