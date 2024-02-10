#include "test.h"

#include "arith_matrix_test.h"

int main(void)
{
    ARITH_TEST(test_matrix_creation());
    ARITH_TEST(test_matrix_multiply());

    return 0;
}