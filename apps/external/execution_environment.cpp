#include "execution_environment.h"
#include <apps/home/app.h>
#include <string.h>

void ExternalExecutionEnvironment::printText(const char * text, size_t length) {
  // TODO: Store the text somewhere
}

// TODO: Use a namespace

bool execute_input(ExternalExecutionEnvironment env, const char * filename) {
  // Use the following syntax to execute a Python script:
  // exec(open("filename").read())
  const char * pythonCodeStart = "exec(open(\"";
  const char * pythonCodeEnd = "\").read())";
  // Initialize the buffer to store the python code (size = 50)
  char pythonCode[50];
  // Add the start of the python code in the buffer (until the file name)
  strlcpy(pythonCode, pythonCodeStart, sizeof(pythonCode));
  // Add the file name in the buffer
  strlcpy(pythonCode + strlen(pythonCode), filename, sizeof(pythonCode) - strlen(pythonCode));
  // Add the end of the python code in the buffer
  strlcpy(pythonCode + strlen(pythonCode), pythonCodeEnd, sizeof(pythonCode) - strlen(pythonCode));
  // Execute the python code
  bool executionResult = env.runCode(pythonCode);
  return executionResult;
}

ExternalExecutionEnvironment init_environnement(void * heap, const uint32_t heapSize) {
  MicroPython::init((uint32_t *)heap, (uint32_t *)heap + heapSize);
  return ExternalExecutionEnvironment();
}

void deinit_environment() {
  MicroPython::deinit();
}
