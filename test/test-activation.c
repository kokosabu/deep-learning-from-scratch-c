#include <cutter.h>
#include <activation.h>

void test_step(void)
{
    cut_assert(step_function(-5)  == 0);
    cut_assert(step_function(0)   == 0);
    cut_assert(step_function(0.1) == 1);
    cut_assert(step_function(5)   == 1);
}
