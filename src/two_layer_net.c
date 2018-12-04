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
    // z1[100][100], a1[100][100]
    z1 = (double **)malloc(sizeof(double *) * x_size);
    for(i = 0; i < x_size; i++) {
        z1[i] = (double *)malloc(sizeof(double) * hidden_size);
        for(j = 0; j < hidden_size; j++) {
            z1[i][j] = sigmoid(a1[i][j]);
        }
    }

    // a2 = np.dot(z1, W2) + b2
    // a2[100][10] = z1[100][100], W2[100][10], b2[10]
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
    double d;
    int i;

    predict(&y, x, hidden_size);

    d = 0;
    for(i = 0; i < hidden_size; i++) {
        d += cross_entropy_error(y[i], t, 10);
    }

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

        x[idx] = tmp_val - h;
        fxh2 = f(a, b);

        (*grad)[idx] = (fxh1 - fxh2) / (2*h);
        x[idx] = tmp_val;
    }
}

void TwoLayerNet_numerical_gradient(double ***grads, double **x, double *t)
{
    double **g_W1;
    double *g_b1;
    double **g_W2;
    double *g_b2;
    //(*grads)[0]

    //numerical_gradient(&g_b1, double (*f)(double *), b1, hidden_size);
    numerical_gradient2(&g_b1, loss, x, t, b1, hidden_size);
}

#if 0
double **get_W(void)
{
    return W;
}
#endif
