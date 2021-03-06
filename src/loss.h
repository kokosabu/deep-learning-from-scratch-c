#ifndef __LOSS_H
#define __LOSS_H

#include <stddef.h>

double mean_squared_error(double *y, double *t, size_t s);
double cross_entropy_error(double *y, double *t, size_t s);

#endif /* __LOSS_H */
