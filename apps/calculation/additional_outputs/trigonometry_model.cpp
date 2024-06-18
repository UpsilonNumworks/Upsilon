#include "trigonometry_model.h"

namespace Calculation {

TrigonometryModel::TrigonometryModel() :
  Shared::CurveViewRange(),
  m_angle(NAN)
{
}

float TrigonometryModel::yMin() const {
  if (m_shouldDisplayTan) {
    return -1.1f;
  }
  return yCenter() - yHalfRange();
}

float TrigonometryModel::yMax() const {
  if (m_shouldDisplayTan) {
    float t = std::tan(angle());
    if (t <= 1.2f) {
      return 1.2f;
    }
    return 1.2f * std::tan(angle());
  }
  return yCenter() + yHalfRange();
}

}
