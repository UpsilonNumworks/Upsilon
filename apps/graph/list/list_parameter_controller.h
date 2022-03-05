#ifndef GRAPH_LIST_LIST_PARAM_CONTROLLER_H
#define GRAPH_LIST_LIST_PARAM_CONTROLLER_H

#include <apps/shared/list_parameter_controller.h>
#include "type_parameter_controller.h"
#include "color_parameter_controller.h"
#include "domain_parameter_controller.h"

namespace Graph {

class ListController;

class ListParameterController : public Shared::ListParameterController {
public:
  ListParameterController(ListController * listController, Responder * parentResponder, I18n::Message functionColorMessage, I18n::Message deleteFunctionMessage, InputEventHandlerDelegate * inputEventHandlerDelegate);
  bool handleEvent(Ion::Events::Event event) override;
  // ListViewDataSource
  HighlightCell * reusableCell(int index, int type) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
protected:
  bool handleEnterOnRow(int rowIndex) override;
private:
  int totalNumberOfCells() const override {
    return Shared::ListParameterController::totalNumberOfCells() + 3;
  }
  void renameFunction();
  ListController * m_listController;
  MessageTableCellWithChevronAndMessage m_typeCell;
  MessageTableCellWithChevronAndBuffer m_functionDomain;
  MessageTableCellWithChevronAndMessage m_colorCell;
  TypeParameterController m_typeParameterController;
  ColorParameterController m_colorParameterController;
  DomainParameterController m_domainParameterController;
  MessageTableCell m_renameCell;
};

}

#endif
