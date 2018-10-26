#include <cutter.h>
#include <loss.h>

void test_mean_squared_error(void)
{
    double y[] = {0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0};
    double t[] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

    printf("%f\n", mean_squared_error(y, t, sizeof(y)/sizeof(y[0])));
    cut_assert(mean_squared_error(y, t, sizeof(y)/sizeof(y[0])) == 0.0975);
}
