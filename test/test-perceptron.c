#include <cutter.h>
#include <perceptron.h>

void test_AND(void)
{
    cut_assert(AND(0, 0) == 0);
    cut_assert(AND(1, 0) == 0);
    cut_assert(AND(0, 1) == 0);
    cut_assert(AND(1, 1) == 1);
}

void test_NAND(void)
{
    cut_assert(NAND(0, 0) == 1);
    cut_assert(NAND(1, 0) == 1);
    cut_assert(NAND(0, 1) == 1);
    cut_assert(NAND(1, 1) == 0);
}

void test_OR(void)
{
    cut_assert(OR(0, 0) == 0);
    cut_assert(OR(1, 0) == 1);
    cut_assert(OR(0, 1) == 1);
    cut_assert(OR(1, 1) == 1);
}

