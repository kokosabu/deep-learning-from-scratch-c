#include <simple_net.h>
#include <stdlib.h>
#include <time.h>
#include <activation.h>
#include <loss.h>

static double **W;

void simpleNet(void)
{
    static int flag = 0;
    int i;
    int j;

    if(flag == 0) {
        flag = 1;
        srand((unsigned int)time(NULL));
    }

    W = (double **)malloc(sizeof(double *) * 2);
    for(i = 0; i < 2; i++) {
        W[i] = (double *)malloc(sizeof(double) * 3);
        for(j = 0; j < 3; j++) {
            W[i][j] = rand() / (double)RAND_MAX;
        }
    }
}

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
