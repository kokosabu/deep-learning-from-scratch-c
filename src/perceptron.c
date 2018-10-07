#include <perceptron.h>

int AND(double x1, double x2)
{
    double x[2];
    static const double w[] = {0.5, 0.5};
    static const double b = -0.7;
    double tmp;
    int i;

    x[0] = x1;
    x[1] = x2;

    tmp = 0;
    for(i = 0; i < (sizeof(w)/sizeof(w[0])); i++) {
        tmp += w[i] * x[i];
    }
    tmp += b;

    if(tmp <= 0) {
        return 0;
    } else {
        return 1;
    }
}

int NAND(double x1, double x2)
{
    double x[2];
    static const double w[] = {-0.5, -0.5};
    static const double b = 0.7;
    double tmp;
    int i;

    x[0] = x1;
    x[1] = x2;

    tmp = 0;
    for(i = 0; i < (sizeof(w)/sizeof(w[0])); i++) {
        tmp += w[i] * x[i];
    }
    tmp += b;

    if(tmp <= 0) {
        return 0;
    } else {
        return 1;
    }
}

int OR(double x1, double x2)
{
    double x[2];
    static const double w[] = {0.5, 0.5};
    static const double b = -0.2;
    double tmp;
    int i;

    x[0] = x1;
    x[1] = x2;

    tmp = 0;
    for(i = 0; i < (sizeof(w)/sizeof(w[0])); i++) {
        tmp += w[i] * x[i];
    }
    tmp += b;

    if(tmp <= 0) {
        return 0;
    } else {
        return 1;
    }
}

