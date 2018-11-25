#include <two_layer_net.h>
#include <mnist.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static void random_choice(int **indexes, int train_size, int batch_size)
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
    uint8_t **x_train_;
    uint8_t *t_train;
    uint8_t **x_test_;
    uint8_t *t_test;
    double **x_train;
    double **x_test;

    uint16_t train_size;
    uint16_t iters_num;
    uint16_t batch_size;
    double learning_rate;

    int i;
    int j;
    int k;
    int *indexes;
    uint8_t **x_batch;
    uint8_t *t_batch;

    read_images(&x_train_, &x_train,  "train-images-idx3-ubyte", 0);
    read_labels(&t_train, "train-labels-idx1-ubyte");
    read_images(&x_test_,  &x_test, "t10k-images-idx3-ubyte", 0);
    read_labels(&t_test,  "t10k-labels-idx1-ubyte");

    train_size = 60000;
    iters_num = 10000;
    batch_size = 100;
    learning_rate = 0.01;

    TwoLayerNet(784, 50, 10, 0.01);

    fprintf(stderr, "ERROR1\n");
    x_batch = (uint8_t **)malloc(sizeof(uint8_t *) * batch_size);
    for(i = 0; i < batch_size; i++) {
        x_batch[i] = (uint8_t *)malloc(sizeof(uint8_t) * 784);
    }
    t_batch = (uint8_t *)malloc(sizeof(uint8_t) * batch_size);
    fprintf(stderr, "ERROR2\n");

    for(i = 0; i < 784; i++) {
        printf("[%d] %d\n", i, x_train_[0][i]);
    }
    for(i = 0; i < iters_num; i++) {
        /* ミニバッチの取得 */
        indexes = NULL;
        random_choice(&indexes, train_size, batch_size);
        for(j = 0; j < batch_size; j++) {
            printf("[%d] %d\n", j, indexes[j]);
            for(k = 0; k < 784; k++) {
                //printf("[%d] %f\n", k, x_train[indexes[j]][k]);
                //printf("[%d] %f\n", k, x_train[0][k]);
                x_batch[j][k] = x_train_[indexes[j]][k];
            }
            t_batch[j] = t_train[indexes[j]];
        }

        /* 勾配の計算 */

        /* パラメータの更新 */

        /* 学習経過の記録 */
    }

    return 0;
}
