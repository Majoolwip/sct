#ifndef SCT_H_
#define SCT_H_

#include <stdio.h>

#define SCT_ASSERT(predicate)           \
  if (!(predicate)) {                   \
    printf("(%s) != true", #predicate); \
    sct_fail_test(state);               \
  }

#define SCT_ASSUME(predicate)                         \
  if (!(predicate)) {                                 \
    printf("Skipped as (%s) was false.", #predicate); \
    sct_skip_test(state);                             \
  }

#define SCT_Test(name) void name(SCT_State *state)

typedef struct SCT_State SCT_State;

typedef struct {
  void (*fn)(SCT_State *state);
  char const *name;
} SCT_Test;

/**
 * \brief Runs the given tests in the order they are given.
 *
 * Prints information about the tests to \c stdout and returns the number of
 * failed tests.
 *
 * \param tests Pointer to an array of SCT_Tests.
 * \param n The number of #SCT_Test in tests.
 * \return The number of failed tests.
 */
int sct_run_tests(SCT_Test *tests, int n);

/**
 * \brief Fails the current test.
 *
 * \param state The test state that this test belongs too.
 */
void sct_fail_test(SCT_State *state);

/**
 * \brief Skips the current test.
 *
 * \param state The test state that this test belongs too.
 */
void sct_skip_test(SCT_State *state);

#endif