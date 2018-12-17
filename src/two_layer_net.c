#include <two_layer_net.h>
#include <stdlib.h>
#include <time.h>
#include <activation.h>
#include <loss.h>
#include <stdio.h>

static double **W1;
static double **W2;
static double *b1;
static double *b2;
static double **grad_W1;
static double **grad_W2;
static double *grad_b1;
static double *grad_b2;
static int input_size;
static int hidden_size;
static int output_size;
static double weight_init_std;
static int loss_flag;

static void activation_array(double dst[], double src[], double (*funcp)(double x), size_t s)
{
    int i;
    for(i = 0; i < s; i++) {
        dst[i] = funcp(src[i]);
    }
}

void TwoLayerNet(int _input_size, int _hidden_size, int _output_size, double _weight_init_std)
{
    static int flag = 0;
    int i;
    int j;

    input_size = _input_size;
    hidden_size = _hidden_size;
    output_size = _output_size;
    weight_init_std = _weight_init_std;

    if(flag == 0) {
        flag = 1;
        srand((unsigned int)time(NULL));
    }

    W1 = (double **)malloc(sizeof(double *) * input_size);
    for(i = 0; i < input_size; i++) {
        W1[i] = (double *)malloc(sizeof(double) * hidden_size);
        for(j = 0; j < hidden_size; j++) {
            W1[i][j] = weight_init_std * (rand() / (double)RAND_MAX);
        }
    }

    b1 = (double *)malloc(sizeof(double) * hidden_size);
    for(i = 0; i < hidden_size; i++) {
        b1[i] = weight_init_std * (rand() / (double)RAND_MAX);
    }

    W2 = (double **)malloc(sizeof(double *) * hidden_size);
    for(i = 0; i < hidden_size; i++) {
        W2[i] = (double *)malloc(sizeof(double) * output_size);
        for(j = 0; j < output_size; j++) {
            W2[i][j] = weight_init_std * (rand() / (double)RAND_MAX);
        }
    }

    b2 = (double *)malloc(sizeof(double) * output_size);
    for(i = 0; i < output_size; i++) {
        b2[i] = weight_init_std * (rand() / (double)RAND_MAX);
    }

    grad_W1 = (double **)malloc(sizeof(double *) * input_size);
    for(i = 0; i < input_size; i++) {
        grad_W1[i] = (double *)malloc(sizeof(double) * hidden_size);
    }
    grad_b1 = (double *)malloc(sizeof(double) * hidden_size);
    grad_W2 = (double **)malloc(sizeof(double *) * hidden_size);
    for(i = 0; i < hidden_size; i++) {
        grad_W2[i] = (double *)malloc(sizeof(double) * output_size);
    }
    grad_b2 = (double *)malloc(sizeof(double) * output_size);

    loss_flag = 0;
}

void predict(double ***y, double **x, size_t x_size)
{
    int i;
    int j;
    int k;
    double **a1;
    double **z1;
    double **a2;

    // a1 = np.dot(x, W1) + b1
    // a1[100][100] = x[100][784(input_size)], W1[784(input_size)][100(hidden_size)], b1[100]
    a1 = (double **)malloc(sizeof(double *) * x_size);
    for(i = 0; i < x_size; i++) {
        a1[i] = (double *)malloc(sizeof(double) * hidden_size);
        for(j = 0; j < hidden_size; j++) {
            a1[i][j] = 0;
            for(k = 0; k < input_size; k++) {
                a1[i][j] += x[j][k] * W1[k][i] + b1[j];
            }
        }
    }

    // z1 = sigmoid(a1)
    z1 = (double **)malloc(sizeof(double *) * x_size);
    for(i = 0; i < x_size; i++) {
        z1[i] = (double *)malloc(sizeof(double) * hidden_size);
        for(j = 0; j < hidden_size; j++) {
            z1[i][j] = sigmoid(a1[i][j]);
            printf("%d %d: %f\n", i, j, z1[i][j]);
        }
    }

    // a2 = np.dot(z1, W2) + b2
    a2 = (double **)malloc(sizeof(double *) * hidden_size);
    for(i = 0; i < hidden_size; i++) {
        a2[i] = (double *)malloc(sizeof(double) * x_size);
        for(j = 0; j < x_size; j++) {
            a2[i][j] = 0;
            for(k = 0; k < output_size; k++) {
                a2[i][j] += z1[j][k] * W2[k][i] + b2[j];
            }
        }
    }

    // y = softmax(a2)
    (*y) = (double **)malloc(sizeof(double *) * hidden_size);
    for(i = 0; i < hidden_size; i++) {
        (*y)[i] = (double *)malloc(sizeof(double) * output_size);
        softmax((*y)[i], a2[i], output_size);
    }
}

double loss(double **x, double *t)
{
    double *z;
    double **y;
    static double d;
    int i;

    //if(loss_flag == 0) {
        predict(&y, x, hidden_size);

        d = 0;
        for(i = 0; i < hidden_size; i++) {
            d += cross_entropy_error(y[i], t, 10);
        }
    //}

    return d;
}

static void argmax(double **a, double **x)
{
    int i;
    int j;
    double max;
    int max_index;

    *a = (double *)malloc(sizeof(double) * 100);

    for(i = 0; i < 100; i++) {
        max = 0;
        max_index = -1;
        for(j = 0; j < 10; j++) {
            if(max < x[i][j]) {
                max = x[i][j];
                max_index = j;
            }
        }
        (*a)[i] = max_index;
    }
}

double accuracy(double **x, double **t)
{
    double **y;
    double *_y;
    double *_t;
    int sum;
    int i;

    predict(&y, x, 100);
    argmax(&_y, y);
    argmax(&_t, t);

    sum = 0;
    for(i = 0; i < 100; i++) {
        if(y[i] == t[i]) {
            sum += 1;
        }
    }

    return (double)sum / 100;
}

void numerical_gradient2(double **grad, double (*f)(double **, double *), double **a, double *b, double *x, size_t s)
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
        fxh1 = f(a, b);
        if(idx == 0) {
            printf("2-1 %f %f\n", x[idx], b1[idx]);
        }

        x[idx] = tmp_val - h;
        fxh2 = f(a, b);
        if(idx == 0) {
            printf("2-2 %f %f\n", x[idx], b1[idx]);
        }

        (*grad)[idx] = (fxh1 - fxh2) / (2*h);
        x[idx] = tmp_val;
    }
}

void numerical_gradient3(double ***grad, double (*f)(double **, double *), double **a, double *b, double **x, size_t s1, size_t s2)
{
    double h;
    double tmp_val;
    double fxh1;
    double fxh2;
    int idx;
    int idx2;

    h = 1e-4;

    *grad = (double **)malloc(sizeof(double *) * s1);

    for(idx = 0; idx < s1; idx++) {
        (*grad)[idx] = (double *)malloc(sizeof(double) * s2);
        for(idx2 = 0; idx2 < s2; idx2++) {
            tmp_val = x[idx][idx2];

            x[idx][idx2] = tmp_val + h;
            fxh1 = f(a, b);

            x[idx][idx2] = tmp_val - h;
            fxh2 = f(a, b);

            (*grad)[idx][idx2] = (fxh1 - fxh2) / (2*h);
            x[idx][idx2] = tmp_val;

            if(idx == 0 && idx2 == 0) {
                printf("%f %f %f %f\n", x[idx][idx2], fxh1, fxh2, (*grad)[idx][idx2]);
            }
        }
    }
}

void TwoLayerNet_numerical_gradient(double ***grads, double **x, double *t)
{
    loss_flag = 0;
    numerical_gradient3(&grad_W1, loss, x, t, W1, input_size, hidden_size);
    numerical_gradient2(&grad_b1, loss, x, t, b1, hidden_size);
    numerical_gradient3(&grad_W2, loss, x, t, W2, hidden_size, output_size);
    numerical_gradient2(&grad_b2, loss, x, t, b2, output_size);
}

double **get_W1(void)
{
    return W1;
}

double **get_W2(void)
{
    return W2;
}

double *get_b1(void)
{
    return b1;
}

double *get_b2(void)
{
    return b2;
}

double **get_grad_W1(void)
{
    return grad_W1;
}

double **get_grad_W2(void)
{
    return grad_W2;
}

double *get_grad_b1(void)
{
    return grad_b1;
}

double *get_grad_b2(void)
{
    return grad_b2;
}

void W1_update(double learning_rate)
{
    int i;
    int j;

    for(i = 0; i < input_size; i++) {
        for(j = 0; j < hidden_size; j++) {
            W1[i][j] -= grad_W1[i][j] * learning_rate;
        }
    }
}

void W2_update(double learning_rate)
{
    int i;
    int j;

    for(i = 0; i < hidden_size; i++) {
        for(j = 0; j < output_size; j++) {
            W2[i][j] -= grad_W2[i][j] * learning_rate;
        }
    }
}

void b1_update(double learning_rate)
{
    int i;

    for(i = 0; i < hidden_size; i++) {
        b1[i] = grad_b1[i] * learning_rate;
    }
}

void b2_update(double learning_rate)
{
    int i;

    for(i = 0; i < output_size; i++) {
        b2[i] -= grad_b2[i] * learning_rate;
    }
}

