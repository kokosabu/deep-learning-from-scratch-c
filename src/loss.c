#include <loss.h>
#include <math.h>
#include <stdlib.h>

double mean_squared_error(double *y, double *t, size_t s)
{
    double loss;
    int i;

    loss = 0;
    for(i = 0; i < s; i++) {
        loss += 0.5 * pow((y[i]-t[i]), 2);
    }

    return loss;
}

double cross_entropy_error(double *y, double *t, size_t s)
{
    double delta;
    double loss;
    int i;

    delta = 1e-7;

    loss = 0;
    for(i = 0; i < s; i++) {
        loss += -1 * t[i] * log(y[i] + delta);
    }

    return loss;
}

