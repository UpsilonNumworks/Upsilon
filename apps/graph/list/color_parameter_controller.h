#pragma once

#include <escher/view_controller.h>
#include <escher/list_view_data_source.h>
#include <escher/selectable_table_view.h>
#include <escher/message_table_cell_with_expression.h>
#include <escher/stack_view_controller.h>
#include <ion/storage.h>

#define NUMBER_OF_COLORS_AVAILABLE 8;

namespace Graph {

class ColorParameterController : public ViewController, public ListViewDataSource, public SelectableTableViewDataSource {
public:
  ColorParameterController(Responder * parentResponder);

  void didBecomeFirstResponder() override;
  bool handleEvent(Ion::Events::Event event) override;

  // ViewController
  const char * title() override;
  View * view() override { return &m_selectableTableView; }
  void viewWillAppear() override;
  TELEMETRY_ID("ColorParameter");

  // ListViewDataSource
  int numberOfRows() const override { return k_numberOfTypes; }
  KDCoordinate rowHeight(int j) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  MessageTableCellWithExpression * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override { return k_numberOfTypes; }
  int typeAtLocation(int i, int j) override { return 0; }

  void setRecord(Ion::Storage::Record record) { m_record = record; }
private:
  constexpr static int k_numberOfTypes = NUMBER_OF_COLORS_AVAILABLE;
  StackViewController * stackController() const;
  SelectableTableView m_selectableTableView;
  MessageTableCellWithExpression m_cells[k_numberOfTypes];
  Ion::Storage::Record m_record;
};

}