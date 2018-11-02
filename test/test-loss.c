#include <cutter.h>
#include <loss.h>

void test_mean_squared_error(void)
{
    double y1[] = {0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0};
    double y2[] = {0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.5, 0.0};
    double t[] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

    cut_assert(mean_squared_error(y1, t, sizeof(y1)/sizeof(y1[0])) >= 0.0975);
    cut_assert(mean_squared_error(y1, t, sizeof(y1)/sizeof(y1[0])) <= 0.0976);
    cut_assert(mean_squared_error(y2, t, sizeof(y2)/sizeof(y2[0])) >= 0.72249);
    cut_assert(mean_squared_error(y2, t, sizeof(y2)/sizeof(y2[0])) <= 0.72251);
}

void test_cross_entropy_error(void)
{
    double y1[] = {0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0};
    double y2[] = {0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.5, 0.0};
    double t[] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

    cut_assert(cross_entropy_error(y1, t, sizeof(y1)/sizeof(y1[0])) >= 0.5108);
    cut_assert(cross_entropy_error(y1, t, sizeof(y1)/sizeof(y1[0])) <= 0.5109);
    cut_assert(cross_entropy_error(y2, t, sizeof(y2)/sizeof(y2[0])) >= 2.3025);
    cut_assert(cross_entropy_error(y2, t, sizeof(y2)/sizeof(y2[0])) <= 2.3026);
}

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
