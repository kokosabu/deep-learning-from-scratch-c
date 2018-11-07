#ifndef __SIMPLE_NET_H
#define __SIMPLE_NET_H

void simpleNet(void);
void predict(double **p, double *x);
double loss(double *x, double *t);
double **get_W(void);

#endif
