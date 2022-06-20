#include "function_active_function_toggle.h"

Ion::Storage::Record Shared::FunctionActiveFunctionToggle::getRecord() {
  if (m_functionStore == nullptr || m_functionStore->numberOfActiveFunctions() <= 0) {
    return Ion::Storage::Record();
  }
  return m_functionStore->activeRecordAtIndex(m_index);
}

void Shared::FunctionActiveFunctionToggle::moveUp() {
  if (m_functionStore == nullptr) {
    return;
  }
  m_index = m_functionStore->numberOfActiveFunctions() <= m_index + 1 ? 0 : m_index + 1;
}

void Shared::FunctionActiveFunctionToggle::moveDown() {
  if (m_functionStore == nullptr) {
    return;
  }
  m_index = 0 > m_index - 1 ? m_functionStore->numberOfActiveFunctions() - 1 : m_index - 1;
}
