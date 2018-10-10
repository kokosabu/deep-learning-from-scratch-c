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
