#ifdef _MSC_VER
#pragma warning( \
    disable : 5045)  // Spectre warning; warning is purely informational.
#endif

#include "sct.h"

#include <setjmp.h>
#include <stdio.h>

#define PASSED 0
#define FAILED 1
#define SKIPPED 2

struct SCT_State {
  jmp_buf jbuf;
};

int sct_run_tests(SCT_Test *tests, int n) {
  SCT_State state;
  int i, jump_value;
  int passed = 0, failed = 0, skipped = 0;

  for (i = 0; i < n; i++) {
    (void)printf("Running '%s' ... ", tests[i].name);
    jump_value = setjmp(state.jbuf);
    switch (jump_value) {
      case PASSED:
        tests[i].fn(&state);
        (void)puts("PASSED!");
        passed++;
        break;
      case FAILED:
        (void)puts(" ... FAILED!");
        failed++;
        break;
      case SKIPPED:
        (void)puts(" ... SKIPPED!");
        skipped++;
        break;
    }
  }
  (void)printf("Finished | %i PASSED | %i FAILED | %i SKIPPED | %i TOTAL\n",
               passed, failed, skipped, n);
  return failed;
}

void sct_fail_test(SCT_State *state) { longjmp(state->jbuf, FAILED); }

void sct_skip_test(SCT_State *state) { longjmp(state->jbuf, SKIPPED); }