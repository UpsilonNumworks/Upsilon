#ifndef CALCULATION_ADDITIONAL_OUTPUTS_TRIGONOMETRY_GRAPH_CELL_H
#define CALCULATION_ADDITIONAL_OUTPUTS_TRIGONOMETRY_GRAPH_CELL_H

#include "../../shared/curve_view.h"
#include "trigonometry_model.h"
#include "illustration_cell.h"

namespace Calculation {

class TrigonometryGraphView : public Shared::CurveView {
public:
  TrigonometryGraphView(TrigonometryModel * model);
  void drawRect(KDContext * ctx, KDRect rect) const override;
  void setShouldDisplayTan(bool shouldDisplayTan) { m_shouldDisplayTan = shouldDisplayTan; };
private:
  TrigonometryModel * m_model;
  bool m_shouldDisplayTan;
};

class TrigonometryGraphCell : public IllustrationCell {
public:
  TrigonometryGraphCell(TrigonometryModel * model) : m_view(model) {}
  void setShouldDisplayTan(bool shouldDisplayTan) { m_view.setShouldDisplayTan(shouldDisplayTan); };
private:
  View * view() override { return &m_view; }
  TrigonometryGraphView m_view;
};

}

#endif

