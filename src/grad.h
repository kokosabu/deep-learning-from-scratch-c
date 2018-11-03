#ifndef __GRAD_H
#define __GRAD_H

#include <stddef.h>

double numerical_diff(double (*f)(double), double x);
double function_1(double x);
void numerical_gradient(double **grad, double (*f)(double *), double *x, size_t s);
double function_2(double *x);
void gradient_descent(double **x, double (*f)(double *), double *init_x, size_t s, double lr, int step_num);

#endif
