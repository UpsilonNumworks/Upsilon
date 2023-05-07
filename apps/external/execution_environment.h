#include <python/port/port.h>
#include <apps/code/app.h>

class ExternalExecutionEnvironment : public MicroPython::ExecutionEnvironment {
public:
  ExternalExecutionEnvironment() : m_printTextIndex(0) {}
  void printText(const char * text, size_t length) override;
  const char * lastPrintedText() const { return m_printTextBuffer; }
private:
  static constexpr size_t k_maxPrintedTextSize = 256;
  char m_printTextBuffer[k_maxPrintedTextSize];
  size_t m_printTextIndex;
};

ExternalExecutionEnvironment init_environnement(void * heap, const uint32_t heapSize);
void deinit_environment();
bool execute_input(ExternalExecutionEnvironment env, const char * filename);
