#pragma once

#include <stdio.h>
#include <string.h>
#include <time.h>

/*
  Color codes
*/
#define CNT_ANSI_COLOR_RED "\x1b[31m"
#define CNT_ANSI_COLOR_GREEN "\x1b[32m"
#define CNT_ANSI_COLOR_YELLOW "\x1b[33m"
#define CNT_ANSI_COLOR_RESET "\x1b[0m"

int cnt_testsRun = 0;
int cnt_testsPassed = 0;
int cnt_testsFailed = 0;
int cnt_testsSkipped = 0;

int cnt_passed;

void cnt_setUp();
void cnt_tearDown();

#define cnt_run(desc, test)                                                                             \
  do                                                                                                    \
  {                                                                                                     \
    clock_t cnt_start, cnt_end;                                                                         \
    double cnt_cpuTimeUsed;                                                                             \
    cnt_start = clock();                                                                                \
    cnt_passed = 1;                                                                                     \
    cnt_setUp();                                                                                        \
    test();                                                                                             \
    cnt_tearDown();                                                                                     \
    cnt_end = clock();                                                                                  \
    cnt_cpuTimeUsed = ((double)(cnt_end - cnt_start)) / CLOCKS_PER_SEC * 1000;                          \
    cnt_testsRun++;                                                                                     \
    if (cnt_passed)                                                                                     \
    {                                                                                                   \
      printf(CNT_ANSI_COLOR_GREEN "PASSED" CNT_ANSI_COLOR_RESET " %s (%fms)\n", desc, cnt_cpuTimeUsed); \
      cnt_testsPassed++;                                                                                \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
      printf(CNT_ANSI_COLOR_RED "FAILED" CNT_ANSI_COLOR_RESET " %s (%fms)\n", desc, cnt_cpuTimeUsed);   \
      cnt_testsFailed++;                                                                                \
    }                                                                                                   \
  } while (0)

#define cnt_skip(desc, test)                                                    \
  do                                                                            \
  {                                                                             \
    printf(CNT_ANSI_COLOR_YELLOW "SKIPPED" CNT_ANSI_COLOR_RESET " %s\n", desc); \
    cnt_testsRun++;                                                             \
    cnt_testsSkipped++;                                                         \
  } while (0)

#define cnt_end()                                                                                                                      \
  do                                                                                                                                   \
  {                                                                                                                                    \
    printf("*** Test suite ");                                                                                                         \
    if (cnt_testsFailed)                                                                                                               \
    {                                                                                                                                  \
      printf(CNT_ANSI_COLOR_RED "FAILED" CNT_ANSI_COLOR_RESET "\n");                                                                   \
    }                                                                                                                                  \
    else                                                                                                                               \
    {                                                                                                                                  \
      printf(CNT_ANSI_COLOR_GREEN "PASSED" CNT_ANSI_COLOR_RESET "\n");                                                                 \
    }                                                                                                                                  \
    printf("Tests run: %d - Passed: %d, Failed: %d, Skipped: %d\n", cnt_testsRun, cnt_testsPassed, cnt_testsFailed, cnt_testsSkipped); \
  } while (0)

#define cnt_fail() \
  cnt_passed = 0;  \
  printf(" failure in %s() %s:%d\n", __func__, __FILE__, __LINE__)

/*
  Assertion macros
*/

#define cnt_assertTrue(test)        \
  do                                \
  {                                 \
    if (!(test))                    \
    {                               \
      cnt_fail();                   \
      printf("  Should be true\n"); \
    }                               \
  } while (0)

#define cnt_assertFalse(test)        \
  do                                 \
  {                                  \
    if (test)                        \
    {                                \
      cnt_fail();                    \
      printf("  Should be false\n"); \
    }                                \
  } while (0)

#define cnt_assertIntEqual(expected, actual)                    \
  do                                                            \
  {                                                             \
    if (expected != actual)                                     \
    {                                                           \
      cnt_fail();                                               \
      printf("  expected: %d, actual: %d\n", expected, actual); \
    }                                                           \
  } while (0)

#define cnt_assertDoubleEqual(expected, actual)                 \
  do                                                            \
  {                                                             \
    if (expected != actual)                                     \
    {                                                           \
      cnt_fail();                                               \
      printf("  expected: %f, actual: %f\n", expected, actual); \
    }                                                           \
  } while (0)

#define cnt_assertStringEqual(expected, actual)                 \
  do                                                            \
  {                                                             \
    if (strcmp(expected, actual))                               \
    {                                                           \
      cnt_fail();                                               \
      printf("  expected: %s, actual: %s\n", expected, actual); \
    }                                                           \
  } while (0)
