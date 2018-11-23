#include <cutter.h>
#include <two_layer_net.h>
#include <grad.h>
#include <time.h>

//double x[] = {0.6, 0.9};
//double t[] = {0, 0, 1};

/*
static double f(double *w)
{
    return loss(x, t);
}
*/

void test_simple_net(void)
{
    double **x;
    double **y;
    double **t;
    int i;
    int j;

    TwoLayerNet(784, 100, 10, 0.01);

    srand((unsigned int)time(NULL));
    x = (double **)malloc(sizeof(double *) * 100);
    for(i = 0; i < 100; i++) {
        x[i] = (double *)malloc(sizeof(double) * 784);
        for(j = 0; j < 784; j++) {
            x[i][j] = (rand() / (double)RAND_MAX);
        }
    }

    predict(&y, x, 100);

    t = (double **)malloc(sizeof(double *) * 100);
    for(i = 0; i < 100; i++) {
        t[i] = (double *)malloc(sizeof(double) * 10);
        for(j = 0; j < 10; j++) {
            t[i][j] = (rand() / (double)RAND_MAX);
        }
    }

    //simpleNet();
    //W = get_W();

    //W[0][0] = 0.47355232;
    //W[0][1] = 0.9977393;
    //W[0][2] = 0.84668094;
    //W[1][0] = 0.85557411;
    //W[1][1] = 0.03563661;
    //W[1][2] = 0.69422093;

    //predict(&p, x);
    //cut_assert(p[0] >= 1.0541480);
    //cut_assert(p[0] <= 1.0541481);
    //cut_assert(p[1] >= 0.6307165);
    //cut_assert(p[1] <= 0.6307166);
    //cut_assert(p[2] >= 1.132807);
    //cut_assert(p[2] <= 1.132808);

    //cut_assert(loss(x, t) >= 0.92806);
    //cut_assert(loss(x, t) <= 0.92807);

    //numerical_gradient(&grad, f, *W, 3);
    //printf("%f\n", grad[0]);
    //printf("%f\n", grad[1]);
    //printf("%f\n", grad[2]);
}

