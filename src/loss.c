#include <loss.h>
#include <math.h>

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
