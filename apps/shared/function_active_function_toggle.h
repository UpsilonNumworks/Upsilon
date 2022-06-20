#ifndef FUNCTION_ACTIVE_FUNCTION_TOGGLE_H
#define FUNCTION_ACTIVE_FUNCTION_TOGGLE_H


#include "../../ion/include/ion/storage.h"
#include "function_store.h"

namespace Shared {

class FunctionActiveFunctionToggle {
public:
  explicit FunctionActiveFunctionToggle(FunctionStore * store) : m_functionStore(store), m_index(0) {}

  Ion::Storage::Record getRecord();
  void setCurrentIndex(int ni) { m_index = ni; }
  void setFunctionStorePtr(FunctionStore * store) { m_functionStore = store; }
  void moveUp();
  void moveDown();

private:
  FunctionStore * m_functionStore;
  int m_index;

};
}

#endif //FUNCTION_ACTIVE_FUNCTION_TOGGLE_H
