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

    double **W1;
    double **W2;
    double *b1;
    double *b2;
    double **grad_W1;
    double **grad_W2;
    double *grad_b1;
    double *grad_b2;

    read_images(&x_train_, &x_train,  "train-images-idx3-ubyte", 0);
    read_labels(&t_train, "train-labels-idx1-ubyte");
    read_images(&x_test_,  &x_test, "t10k-images-idx3-ubyte", 0);
    read_labels(&t_test,  "t10k-labels-idx1-ubyte");

    train_size = 60000;
    //iters_num = 10000;
    iters_num = 1;
    batch_size = 100;
    learning_rate = 0.01;

    train_loss_list = (double *)malloc(sizeof(double) * iters_num);

    //TwoLayerNet(784, 50, 10, 0.01);
    TwoLayerNet(784, 50, 10, 0.001);

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

        W1 = get_W1();
        b1 = get_b1();
        W2 = get_W2();
        b2 = get_b2();

        grad_W1 = get_grad_W1();
        grad_b1 = get_grad_b1();
        grad_W2 = get_grad_W2();
        grad_b2 = get_grad_b2();

        printf("W1[0][0] = %f\n", W1[0][0]);
        printf("b1[0]    = %f\n", b1[0]);
        printf("W2[0][0] = %f\n", W2[0][0]);
        printf("b2[0]    = %f\n", b2[0]);
        printf("grad_W1[0][0] = %f\n", grad_W1[0][0]);
        printf("grad_b1[0]    = %f\n", grad_b1[0]);
        printf("grad_W2[0][0] = %f\n", grad_W2[0][0]);
        printf("grad_b2[0]    = %f\n", grad_b2[0]);

        /* パラメータの更新 */
        W1_update(learning_rate);
        b1_update(learning_rate);
        W2_update(learning_rate);
        b2_update(learning_rate);

        /* 学習経過の記録 */
        train_loss_list[i] = loss(x_batch, t_batch);
        printf("%d %f\n", i, train_loss_list[i]);
    }

    return 0;
}
