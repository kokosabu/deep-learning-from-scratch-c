#include <cutter.h>
#include <simple_net.h>

void test_simple_net(void)
{
    double **W;
    int i;
    int j;
    double x[] = {0.6, 0.9};
    double *p;
    double t[] = {0, 0, 1};

    simpleNet();
    W = get_W();

    //W[0][0] = 
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 3; j++) {
            printf("%f ", W[i][j]);
        }
        printf("\n");
    }

    predict(&p, x);

    for(i = 0; i < 3; i++) {
        printf("%f ", p[i]);
    }
    printf("\n");

    printf("%f\n", loss(x, t));
}
