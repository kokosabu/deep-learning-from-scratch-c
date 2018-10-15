#ifndef __ACTIVATION_H

#include <stddef.h>

double step_function(double x);
double sigmoid(double x);
double relu(double x);
double identity_function(double x);

void softmax(double y[], double a[], size_t s);

#endif /* __ACTIVATION_H */
