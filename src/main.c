#include <stdio.h>
#include <activation.h>
#include <stdlib.h>
#include <time.h>

#define dot(a, x, w, row, col)\
    {\
        int i;\
        int j;\
        for(i = 0; i < (row); i++) {\
            (a)[i] = 0;\
            for(j = 0; j < (col); j++) {\
                (a)[i] += w[j][i] * x[j];\
            }\
        }\
    }

void add_array(double dst[], double src[], size_t s)
{
    int i;
    for(i = 0; i < s; i++) {
        dst[i] += src[i];
    }
}

void array_pinrt(double a[], size_t s)
{
    int i;
    for(i = 0; i < s; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");
}

void activation_array(double dst[], double src[], double (*funcp)(double x), size_t s)
{
    int i;
    for(i = 0; i < s; i++) {
        dst[i] = funcp(src[i]);
    }
}

void random_choice(int **indexes, int train_size, int batch_size)
{
    static int rand_flag = 0;
    int i;

    if(rand_flag == 0) {
        srand((unsigned int)time(NULL));
        rand_flag = 1;
    }

    if(*indexes == NULL) {
        *indexes = (int *)malloc(sizeof(int) * batch_size);
    }

    for(i = 0; i < batch_size; i++) {
        (*indexes)[i] = rand()%train_size;
    }
}

int main()
{
    double X[2] = {1.0, 0.5};
    double W1[2][3] = { {0.1, 0.3, 0.5}, {0.2, 0.4, 0.6} };
    double B1[3] = {0.1, 0.2, 0.3};
    double A1[3];
    double Z1[3];
    double W2[3][2] = { {0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6} };
    double B2[2] = {0.1, 0.2};
    double A2[2];
    double Z2[2];
    double W3[2][2] = { {0.1, 0.3}, {0.2, 0.4} };
    double B3[2] = {0.1, 0.2};
    double A3[2];
    double Y[2];

    int *indexes;
    int i;
    
    dot(A1, X, W1, 3, 2);
    add_array(A1, B1, sizeof(A1)/sizeof(A1[0]));
    activation_array(Z1, A1, sigmoid, sizeof(Z1)/sizeof(Z1[0]));

    dot(A2, Z1, W2, 2, 3);
    add_array(A2, B2, sizeof(A2)/sizeof(A2[0]));
    activation_array(Z2, A2, sigmoid, sizeof(Z2)/sizeof(Z2[0]));

    dot(A3, Z2, W3, 2, 2);
    add_array(A3, B3, sizeof(A3)/sizeof(A3[0]));
    activation_array(Y, A3, identity_function, sizeof(Y)/sizeof(Y[0]));

    array_pinrt(A1, sizeof(A1)/sizeof(A1[0]));
    array_pinrt(Z1, sizeof(Z1)/sizeof(Z1[0]));
    array_pinrt(A2, sizeof(A2)/sizeof(A2[0]));
    array_pinrt(Z2, sizeof(Z2)/sizeof(Z2[0]));
    array_pinrt(A3, sizeof(A3)/sizeof(A3[0]));
    array_pinrt(Y, sizeof(Y)/sizeof(Y[0]));


    indexes = NULL;
    random_choice(&indexes, 60000, 10);
    for(i = 0; i < 10; i++) {
        printf("[%d] %d\n", i, indexes[i]);
    }

    return 0;
}
