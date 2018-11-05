#include <simple_net.h>
#include <stdlib.h>
#include <time.h>

static double **W;

void simpleNet(void)
{
    static int flag = 0;
    int i;

    if(flag == 0) {
        flag = 1;
        srand((unsigned int)time(NULL));
    }

    W = (double **)malloc(sizeof(double *) * 2);
    for(i = 0; i < 3; i++) {
        W[i] = (double *)malloc(sizeof(double) * 3);
    }
}
