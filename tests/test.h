#ifndef ARITH_TEST_H
#define ARITH_TEST_H

#include "defines.h"

#define ARITH_TEST_MSG(cond, msg, ...) test_impl((cond), msg, ##__VA_ARGS__)
// the # makes cond into a string
#define ARITH_TEST(cond) test_impl((cond), "%s\n", #cond)

void test_impl(bool success, const char* msg, ...);


#endif