#include <activation.h>
#include <math.h>

double step_function(double x)
{
    if(x > 0) {
        return 1.0;
    } else {
        return 0.0;
    }
}

double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double relu(double x)
{
    if(x < 0) {
        return 0;
    } else {
        return x;
    }
}

double identity_function(double x)
{
    return x;
}

void softmax(double y[], double a[], size_t s)
{
    int i;
    double sum_exp;

    sum_exp = 0.0;
    for(i = 0; i < s; i++) {
        sum_exp += exp(a[i]);
    }

    for(i = 0; i < s; i++) {
        y[i] = exp(a[i]) / sum_exp;
    }
}
