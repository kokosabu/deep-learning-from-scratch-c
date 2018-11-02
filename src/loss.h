#ifndef __LOSS_H
#define __LOSS_H

#include <stddef.h>

double mean_squared_error(double *y, double *t, size_t s);
double cross_entropy_error(double *y, double *t, size_t s);
double numerical_diff(double (*f)(double), double x);
double function_1(double x);
void numerical_gradient(double **grad, double (*f)(double *), double *x, size_t s);
double function_2(double *x);

#endif /* __LOSS_H */
