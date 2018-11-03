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

