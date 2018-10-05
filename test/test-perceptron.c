#include <cutter.h>
#include <perceptron.h>

void test_AND(void)
{
    cut_assert(AND(0, 0) == 0);
    cut_assert(AND(1, 0) == 0);
    cut_assert(AND(0, 1) == 0);
    cut_assert(AND(1, 1) == 1);
}
