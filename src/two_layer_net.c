#include <two_layer_net.h>
#include <stdlib.h>
#include <time.h>
#include <activation.h>
#include <loss.h>

static double **W1;
static double **W2;
static double *b1;
static double *b2;
static int input_size;
static int hidden_size;
static int output_size;
static double weight_init_std;

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
}

void predict(double **y, double **x, size_t x_size)
{
    int i;
    int j;
    int k;
    double **a1;

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

    // a2 = np.dot(z1, W2) + b2
    // a2[100][10] = z1[100][100], W2[100][10], b2[10]

    // y = softmax(a2)

}

#if 0
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
