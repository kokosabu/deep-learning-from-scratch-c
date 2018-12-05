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
    double **x_batch;
    double *t_batch;
    double **grads;
    double *train_loss_list;

    read_images(&x_train_, &x_train,  "train-images-idx3-ubyte", 0);
    read_labels(&t_train, "train-labels-idx1-ubyte");
    read_images(&x_test_,  &x_test, "t10k-images-idx3-ubyte", 0);
    read_labels(&t_test,  "t10k-labels-idx1-ubyte");

    train_size = 60000;
    //iters_num = 10000;
    iters_num = 10;
    batch_size = 100;
    learning_rate = 0.01;

    train_loss_list = (double *)malloc(sizeof(double) * iters_num);

    TwoLayerNet(784, 50, 10, 0.01);

    x_batch = (double **)malloc(sizeof(double *) * batch_size);
    for(i = 0; i < batch_size; i++) {
        x_batch[i] = (double *)malloc(sizeof(double) * 784);
    }
    t_batch = (double *)malloc(sizeof(double) * batch_size);

    for(i = 0; i < iters_num; i++) {
        /* ミニバッチの取得 */
        indexes = NULL;
        random_choice(&indexes, train_size, batch_size);
        for(j = 0; j < batch_size; j++) {
            for(k = 0; k < 784; k++) {
                x_batch[j][k] = x_train_[indexes[j]][k];
            }
            t_batch[j] = t_train[indexes[j]];
        }

        /* 勾配の計算 */
        TwoLayerNet_numerical_gradient(&grads, x_batch, t_batch);

        /* パラメータの更新 */
        //get_b1();
        //update_b1();
        //W1_update(learning_rate, grads);

        /* 学習経過の記録 */
        train_loss_list[i] = loss(x_batch, t_batch);
    }

    return 0;
}
