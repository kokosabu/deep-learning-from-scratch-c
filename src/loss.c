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

double numerical_diff(double (*f)(double), double x)
{
    double h;

    h = 1e-4;
    return (f(x+h) - f(x-h)) / (2*h);
}

double function_1(double x)
{
    return 0.01*pow(x, 2) + 0.1*x;
}

void numerical_gradient(double **grad, double (*f)(double *), double *x, size_t s)
{
    double h;
    double tmp_val;
    double fxh1;
    double fxh2;
    int idx;

    h = 1e-4;

    *grad = (double *)malloc(sizeof(double) * s);

    for(idx = 0; idx < s; idx++) {
        tmp_val = x[idx];

        x[idx] = tmp_val + h;
        fxh1 = f(x);

        x[idx] = tmp_val - h;
        fxh2 = f(x);

        (*grad)[idx] = (fxh1 - fxh2) / (2*h);
        x[idx] = tmp_val;
    }
}

double function_2(double *x)
{
    return pow(x[0], 2) + pow(x[1], 2);
}
