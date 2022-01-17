#include "sct.h"

#include <string.h>

SCT_Test(assert_test_true){SCT_ASSERT(1 == 1)}

SCT_Test(assert_test_false){SCT_ASSERT(1 == 2)}

SCT_Test(assume_true){SCT_ASSUME(1 == 1)}

SCT_Test(assume_false){SCT_ASSUME(1 == 2)}

SCT_Test(test_execution) {
  static char buffer[1028];
  int test_run_return = 0;

  // Capture printf's output for asserting.
  setvbuf(stdout, buffer, _IOFBF, 1028);

  SCT_Test tests[] = {{.fn = assert_test_true, .name = "assert_test_true"},
                      {.fn = assert_test_false, .name = "assert_test_false"},
                      {.fn = assume_true, .name = "assume_true"},
                      {.fn = assume_false, .name = "assume_false"}};
  test_run_return = sct_run_tests(tests, sizeof(tests) / sizeof(tests[0]));
  SCT_ASSERT(test_run_return == 1)
  SCT_ASSERT(
      strncmp(buffer,
              "Running 'assert_test_true' ... PASSED!\nRunning "
              "'assert_test_false' ... (1 == 2) != true ... FAILED!\nRunning "
              "'assume_true' ... PASSED!\nRunning 'assume_false' ... Skipped "
              "as (1 == 2) was false. ... SKIPPED!\nFinished | 2 PASSED | 1 "
              "FAILED | 1 SKIPPED | 4 TOTAL\n",
              1028) == 0)

  // Clear stdout's buffer so nothing is actually printed.
  memset(buffer, 0, 1028);
}

int main(char *args) {
  (void)args;
  SCT_Test tests[] = {{.fn = test_execution, .name = "test_execution"}};
  return sct_run_tests(tests, sizeof(tests) / sizeof(tests[0]));
}