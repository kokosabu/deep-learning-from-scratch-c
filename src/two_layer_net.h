#ifndef __TWO_LAYER_NET_H
#define __TWO_LAYER_NET_H

#include <stddef.h>

void TwoLayerNet(int _input_size, int _hidden_size, int _output_size, double _weight_init_std);
void predict(double ***y, double **x, size_t x_size);
double loss(double **x, double *t);
double accuracy(double **x, double **t);
void TwoLayerNet_numerical_gradient(double ***grads, double **x, double *t);
double **get_W1(void);
double **get_W2(void);
double *get_b1(void);
double *get_b2(void);
double **get_grad_W1(void);
double **get_grad_W2(void);
double *get_grad_b1(void);
double *get_grad_b2(void);

void W1_update(double learning_rate);
void W2_update(double learning_rate);
void b1_update(double learning_rate);
void b2_update(double learning_rate);

#endif
