#include <grad.h>
#include <math.h>
#include <stdlib.h>

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

void gradient_descent(double **x, double (*f)(double *), double *init_x, size_t s, double lr, int step_num)
{
    int i;
    int j;
    double *grad;

    *x = (double *)malloc(sizeof(double) * s);
    for(i = 0; i < s; i++) {
        (*x)[i] = init_x[i];
    }

    for(i = 0; i < step_num; i++) {
        numerical_gradient(&grad, f, *x, s);
        for(j = 0; j < s; j++) {
            (*x)[j] -= lr * grad[j];
        }
        free((void *)grad);
    }
}
