#include <perceptron.h>

int AND(double x1, double x2)
{
    double w1;
    double w2;
    double theta;
    double tmp;

    w1 = 0.5;
    w2 = 0.5;
    theta = 0.7;

    tmp = x1*w1 + x2*w2;

    if(tmp <= theta) {
        return 0;
    } else if(tmp > theta) {
        return 1;
    }

    return -1;
}
