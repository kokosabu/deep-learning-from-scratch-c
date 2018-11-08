#include <simple_net.h>
#include <stdlib.h>
#include <time.h>
#include <activation.h>
#include <loss.h>

static double **W1;
static double **W2;
static double *b1;
static double *b2;

void TwoLayerNet(int input_size, int hidden_size, int output_size, double weight_init_std)
{
    static int flag = 0;
    int i;
    int j;

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
}

#if 0
void predict(double **p, double *x)
{
    int i;
    int j;

    *p = (double *)malloc(sizeof(double) * 3);
    for(i = 0; i < 3; i++) {
        (*p)[i] = 0;
        for(j = 0; j < 2; j++) {
            (*p)[i] += W[j][i] * x[j];
        }
    }
}

double loss(double *x, double *t)
{
    double *z;
    double y[3];

    predict(&z, x);
    softmax(y, z, 3);
    return cross_entropy_error(y, t, 3);
}

double **get_W(void)
{
    return W;
}
#endif
