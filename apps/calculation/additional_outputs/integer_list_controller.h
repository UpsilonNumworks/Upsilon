#ifndef CALCULATION_ADDITIONAL_OUTPUTS_INTEGER_LIST_CONTROLLER_H
#define CALCULATION_ADDITIONAL_OUTPUTS_INTEGER_LIST_CONTROLLER_H

#include "expressions_list_controller.h"

namespace Calculation {

class IntegerListController : public ExpressionsListController {
public:
  IntegerListController(EditExpressionController * editExpressionController) :
    ExpressionsListController(editExpressionController), m_exponent(0) {}

  void setExpression(Poincare::Expression e) override;

  bool handleEvent(Ion::Events::Event event) override;

private:
  void refreshScientificDisplay();
  static constexpr int k_indexOfFactorExpression = 4;
  I18n::Message messageAtIndex(int index) override;
  int m_exponent;
};

}

#endif


