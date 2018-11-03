#include <cutter.h>
#include <grad.h>

void test_numerical_diff(void)
{
    cut_assert(numerical_diff(function_1, 5)  >= 0.1999);
    cut_assert(numerical_diff(function_1, 5)  <= 0.2000);
    cut_assert(numerical_diff(function_1, 10) >= 0.2999);
    cut_assert(numerical_diff(function_1, 10) <= 0.3000);
}

void test_numerical_gradient(void)
{
    double *grad;
    double x[2];

    x[0] = 3.0;
    x[1] = 4.0;
    numerical_gradient(&grad, function_2, x, sizeof(x)/sizeof(x[0]));
    cut_assert(grad[0] >= 5.99);
    cut_assert(grad[0] <= 6.01);
    cut_assert(grad[1] >= 7.99);
    cut_assert(grad[1] <= 8.01);
    free((void *)grad);

    x[0] = 0.0;
    x[1] = 2.0;
    numerical_gradient(&grad, function_2, x, sizeof(x)/sizeof(x[0]));
    cut_assert(grad[0] >= -0.01);
    cut_assert(grad[0] <=  0.01);
    cut_assert(grad[1] >=  3.99);
    cut_assert(grad[1] <=  4.01);
    free((void *)grad);

    x[0] = 3.0;
    x[1] = 0.0;
    numerical_gradient(&grad, function_2, x, sizeof(x)/sizeof(x[0]));
    cut_assert(grad[0] >=  5.99);
    cut_assert(grad[0] <=  6.01);
    cut_assert(grad[1] >= -0.01);
    cut_assert(grad[1] <=  0.01);
    free((void *)grad);
}

