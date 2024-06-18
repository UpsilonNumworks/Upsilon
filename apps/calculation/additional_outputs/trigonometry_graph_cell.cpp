#include "trigonometry_graph_cell.h"
#include <escher/palette.h>

using namespace Shared;
using namespace Poincare;

namespace Calculation {

TrigonometryGraphView::TrigonometryGraphView(TrigonometryModel * model) :
  CurveView(model),
  m_model(model),
  m_shouldDisplayTan(false)
{
}

void TrigonometryGraphView::drawRect(KDContext * ctx, KDRect rect) const {
  float s = std::sin(m_model->angle());
  float c = std::cos(m_model->angle());
  ctx->fillRect(rect, Palette::BackgroundApps);
  drawGrid(ctx, rect);
  drawAxes(ctx, rect);
  // Draw the circle
  drawCurve(ctx, rect, 0.0f, 2.0f*M_PI, M_PI/180.0f, [](float t, void * model, void * context) {
      return Poincare::Coordinate2D<float>(std::cos(t), std::sin(t));
    }, nullptr, nullptr, true, Palette::SecondaryText, false);

  if (!m_shouldDisplayTan) {
    // Draw dashed segment to indicate sine and cosine
    drawHorizontalOrVerticalSegment(ctx, rect, Axis::Vertical, c, 0.0f, s, Palette::CalculationTrigoAndComplexForeground, 1, 3);
    drawHorizontalOrVerticalSegment(ctx, rect, Axis::Horizontal, s, 0.0f, c, Palette::CalculationTrigoAndComplexForeground, 1, 3);
  }

  if (m_shouldDisplayTan) {
    float t = std::tan(m_model->angle());
    drawHorizontalOrVerticalSegment(ctx, rect, Axis::Vertical, 1.0f, m_model->yMin(), m_model->yMax(), Palette::SecondaryText, 2);
    drawSegment(ctx, rect, 0.0f, 0.0f, 1.0f, t, Palette::SecondaryText, false);
    drawDot(ctx, rect, 1.0f, t, Palette::CalculationTrigoAndComplexForeground, Size::Large);
    drawLabel(ctx, rect, 0.0f, t, "tan(θ)", Palette::CalculationTrigoAndComplexForeground, CurveView::RelativePosition::Before, CurveView::RelativePosition::None);
    drawHorizontalOrVerticalSegment(ctx, rect, Axis::Horizontal, t, 0.0f, 1.0f, Palette::CalculationTrigoAndComplexForeground, 1, 3);
  }

  // Draw angle position on the circle
  drawDot(ctx, rect, c, s, m_shouldDisplayTan ? Palette::SecondaryText : Palette::CalculationTrigoAndComplexForeground, m_shouldDisplayTan ? Size::Tiny : Size::Large);
  // Draw graduations
  drawLabelsAndGraduations(ctx, rect, Axis::Vertical, false, true);
  drawLabelsAndGraduations(ctx, rect, Axis::Horizontal, false, true);

  if (!m_shouldDisplayTan) {
    // Draw labels
    drawLabel(ctx, rect, 0.0f, s, "sin(θ)", Palette::CalculationTrigoAndComplexForeground, c >= 0.0f ? CurveView::RelativePosition::Before : CurveView::RelativePosition::After, CurveView::RelativePosition::None);
    drawLabel(ctx, rect, c, 0.0f, "cos(θ)", Palette::CalculationTrigoAndComplexForeground, CurveView::RelativePosition::None, s >= 0.0f ? CurveView::RelativePosition::Before : CurveView::RelativePosition::After);
  }
}

}
