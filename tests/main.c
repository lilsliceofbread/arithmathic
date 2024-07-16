#include "test.h"

#include "arith_matrix_test.h"
#include "arith_complex_test.h"
#include "arith_parser_test.h"

int main(void)
{
    ARITH_TEST(test_matrix_creation());
    ARITH_TEST(test_matrix_multiply());

    ARITH_TEST(test_tokenise_expression());
    ARITH_TEST(test_evaluate_expression());

    /*
    ARITH_TEST(test_complex_to_polar());
    ARITH_TEST(test_complex_to_cartesian());
    ARITH_TEST(test_complex_multiply());
    ARITH_TEST(test_complex_divide());
    ARITH_TEST(test_complex_pow());
    */

    return 0;
}