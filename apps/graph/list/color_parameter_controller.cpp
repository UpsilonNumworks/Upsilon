#include "color_parameter_controller.h"
#include <apps/i18n.h>
#include "../app.h"
#include "color_list.h"
#include <assert.h>

namespace Graph {
    ColorParameterController::ColorParameterController(Responder * parentResponder) :
    ViewController(parentResponder),
    m_selectableTableView(this, this, this, nullptr),
    m_record()
    {
    }

    void ColorParameterController::didBecomeFirstResponder() {
    Container::activeApp()->setFirstResponder(&m_selectableTableView);
    }

    bool ColorParameterController::handleEvent(Ion::Events::Event event) {
    if (event == Ion::Events::OK || event == Ion::Events::EXE) {
        assert(!m_record.isNull());
        App * myApp = App::app();
        assert(!m_record.isNull());
        Shared::ExpiringPointer<Shared::ContinuousFunction> function = myApp->functionStore()->modelForRecord(m_record);
        function->changeColor(FunctionColors::color(selectedRow()));
        StackViewController * stack = stackController();
        stack->pop();
        stack->pop();
        return true;
    }
    if (event == Ion::Events::Left && !m_record.isNull()) {
        stackController()->pop();
        return true;
    }
    return false;
    }

    const char * ColorParameterController::title() {
    return I18n::translate(I18n::Message::FunctionColor);
    }

    void ColorParameterController::viewWillAppear() {
    ViewController::viewWillAppear();
    App * myApp = App::app();
    assert(!m_record.isNull());
    Shared::ExpiringPointer<Shared::ContinuousFunction> function = myApp->functionStore()->modelForRecord(m_record);
    int row = static_cast<int>(function->plotType());
    selectCellAtLocation(0, row);
    m_selectableTableView.reloadData();
    }

    KDCoordinate ColorParameterController::rowHeight(int j) {
        return 30;
    }

    void ColorParameterController::willDisplayCellForIndex(HighlightCell * cell, int index) {
    assert(0 <= index && index < k_numberOfTypes);
    MessageTableCellWithExpression * myCell = static_cast<MessageTableCellWithExpression *>(cell);
    myCell->setMessage(FunctionColors::Message(index));
    myCell->setTextColor(FunctionColors::color(index));
    }

    MessageTableCellWithExpression * ColorParameterController::reusableCell(int index, int type) {
    assert(0 <= index && index < reusableCellCount(type));
    return &m_cells[index];
    }

    StackViewController * ColorParameterController::stackController() const {
    return static_cast<StackViewController *>(parentResponder());
    }

}