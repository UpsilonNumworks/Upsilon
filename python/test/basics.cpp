#include <quiz.h>
#include "execution_environment.h"

QUIZ_CASE(python_basics) {
  TestExecutionEnvironment env = init_environement();
  assert_command_execution_succeeds(env, "2+3","5\n");
  deinit_environment();
}

// No "base" scripts to test.
// QUIZ_CASE(python_template) {

// }
