# `cnt`
Minimalistic unit test framework written in C, inspired by [MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html). Ideal for TDD.

## Naming
`cnt` stands for C UNit Testing, however U was dropped for obvious reasons.

## Features
- One header file
- Simple syntax
- xUnit-style assertions
- Multiple assertions in one test
- Setup / Teardown
- Ability to skip tests
- Easily extensible for custom assertions

## Usage
Testing `sqrt()` from the standard library:
```c
// tests.c
#include <math.h>

// include cnt
#include "cnt.h"

// setup and teardown runs before/after each test
// it's mandatory but can be empty
void cnt_setUp()
{
}

void cnt_tearDown()
{
}

// write your tests
// a test is a function with no arguments returning nothing
// should always contain at least one assertion
void test_sqrt_int()
{
  cnt_assertTrue(sqrt(25) == 5);
  // or
  cnt_assertIntEqual(3, (int)sqrt(9));
}

void test_sqrt_double()
{
  cnt_assertDoubleEqual(round(1.414214*1000000)/1000000,\
   round(sqrt(2)*1000000)/1000000);
}

// this test is unrelevant, so we'll skip it
void test_sqrt_dummy()
{
  cnt_assertStringEqual("this is the expected string", "this is the actual");
}


// this is your "test runner"
int main()
{
  // list all the tests you want to run here
  // cnt_run's first parameter is the description of the test,
  // the second param is the function containing the test
  cnt_run("Should correctly calculate integer values", test_sqrt_int);
  cnt_run("Should calculate the rounded square root of 2", test_sqrt_double);

  // skip this test
  cnt_skip("Totally unrelated test", test_sqrt_dummy);
  
  // add this to print a summary of the whole test suite at the end of the output
  cnt_end();
}
```
Compile `tests.c` and run the tests with `./tests`

The output should be something like this:
```
./tests
PASSED Should correctly calculate integer values (0.000000ms)
PASSED Should calculate the rounded square root of 2 (0.000000ms)
SKIPPED Totally unrelated test
*** Test suite PASSED
Tests run: 3 - Passed: 2, Failed: 0, Skipped: 1
```
(The last two lines come from `cnt_end`.)

## Adding New Assertions

Assertions are simple macros. It's easy to add new ones by defining them in the file containing your test suite. 

Let's assume we want to test a 2d library that defines a point as follows
```c
typedef struct {int x; int y;} Point;
```
and we need a `cnt_assertPointEqual` assertion:
```c
// test_point.c
#include "cnt.h"
#include "our_2d_lib.h"

#define cnt_assertPointEqual(expected, actual)                  \
  do                                                            \
  {                                                             \
    if ((expected.x != actual.x) ||                             \
     (expected.y != actual.y))                                  \
    {                                                           \
      cnt_fail();                                               \
      printf("  expected: (%d, %d), actual: (%d, %d)\n",        \ 
        expected.x, expected.y, actual.x, actual.y);            \
    }                                                           \
  } while (0)

// tests...
```

## Todo
- Ability to abort on first failure
- More assertions
- Add fixtures