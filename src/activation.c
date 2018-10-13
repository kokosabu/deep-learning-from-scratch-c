#include <activation.h>
#include <math.h>

double step_function(double x)
{
    if(x > 0) {
        return 1.0;
    } else {
        return 0.0;
    }
}

double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double relu(double x)
{
    if(x < 0) {
        return 0;
    } else {
        return x;
    }
}

double identity_function(double x)
{
    return x;
}
