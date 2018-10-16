#include <activation.h>
#include <math.h>
#include <float.h>

static double max(double a[], size_t s)
{
    int i;
    double m;

    m = DBL_MIN;

    for(i = 0; i < s; i++) {
        if(a[i] > m) {
            m = a[i];
        }
    }

    return m;
}

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
    double c;

    c = max(a, s);

    sum_exp = 0.0;
    for(i = 0; i < s; i++) {
        sum_exp += exp(a[i] - c);
    }

    for(i = 0; i < s; i++) {
        y[i] = exp(a[i] - c) / sum_exp;
    }
}
