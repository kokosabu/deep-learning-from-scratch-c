#include <cutter.h>
#include <activation.h>

void test_step(void)
{
    cut_assert(step_function(-5)  == 0.0);
    cut_assert(step_function(0)   == 0.0);
    cut_assert(step_function(0.1) == 1.0);
    cut_assert(step_function(5)   == 1.0);
}

void test_sigmoid(void)
{
    cut_assert(sigmoid(-1.0) >= 0.268);
    cut_assert(sigmoid(-1.0) <= 0.269);

    cut_assert(sigmoid(0)   == 0.5);

    cut_assert(sigmoid(1.0) >= 0.731);
    cut_assert(sigmoid(1.0) <= 0.732);
}

void test_relu(void)
{
    cut_assert(relu(-5)  == 0.0);
    cut_assert(relu(0)   == 0.0);
    cut_assert(relu(0.1) == 0.1);
    cut_assert(relu(5)   == 5.0);
}

void test_identity_function(void)
{
    cut_assert(identity_function(-5)  == -5);
    cut_assert(identity_function(0)   == 0);
    cut_assert(identity_function(0.1) == 0.1);
    cut_assert(identity_function(5)   == 5);
}

void test_softmax(void)
{
    double x[3] = {0.3, 2.9, 4.0};
    double y[3];

    softmax(y, x, sizeof(x)/sizeof(x[0]));

    cut_assert(y[0] >= 0.0182);
    cut_assert(y[0] <= 0.0183);
    cut_assert(y[1] >= 0.2451);
    cut_assert(y[1] <= 0.2452);
    cut_assert(y[2] >= 0.7365);
    cut_assert(y[2] <= 0.7366);
}

