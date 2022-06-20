#ifndef GRAPH_TANGENT_GRAPH_CONTROLLER_H
#define GRAPH_TANGENT_GRAPH_CONTROLLER_H

#include "graph_view.h"
#include "banner_view.h"
#include "graph_controller_helper.h"
#include "../../shared/simple_interactive_curve_view_controller.h"
#include "../../shared/function_banner_delegate.h"
#include "apps/shared/function_active_function_toggle.h"

namespace Graph {

class TangentGraphController : public Shared::SimpleInteractiveCurveViewController, public Shared::FunctionBannerDelegate, public GraphControllerHelper {
public:
  TangentGraphController(Responder * parentResponder, GraphView * graphView, BannerView * bannerView, Shared::InteractiveCurveViewRange * curveViewRange, Shared::CurveViewCursor * cursor);
  const char * title() override;
  void viewWillAppear() override;
  void didBecomeFirstResponder() override;
  TELEMETRY_ID("Tangent");
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;
  void setRecordDelegate(Shared::FunctionActiveFunctionToggle * record);
private:
  float cursorBottomMarginRatio() override { return 0.22f; }
  Shared::InteractiveCurveViewRange * interactiveCurveViewRange() override { return m_graphRange; }
  Shared::CurveView * curveView() override { return m_graphView; }
  BannerView * bannerView() override { return m_bannerView; };
  void reloadBannerView() override;
  bool moveCursorHorizontally(int direction, int scrollSpeed = 1) override;

public:
  bool handleEvent(Ion::Events::Event event) override;

private:
  bool handleEnter() override;
  GraphView * m_graphView;
  BannerView * m_bannerView;
  Shared::InteractiveCurveViewRange * m_graphRange;
  Shared::FunctionActiveFunctionToggle * m_recordDelegate;
};

}

#endif
