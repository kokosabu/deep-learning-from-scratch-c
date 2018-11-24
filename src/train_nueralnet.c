#include <two_layer_net.h>
#include <mnist.h>

int main()
{
    uint8_t **train_pixels;
    uint8_t *train_labels;
    uint8_t **test_pixels;
    uint8_t *test_labels;
    double **train_pixels_normalize;
    double **test_pixels_normalize;

    uint16_t iters_num;

    read_images(&train_pixels, &train_pixels_normalize,  "train-images-idx3-ubyte", 0);
    read_labels(&train_labels, "train-labels-idx1-ubyte");
    read_images(&test_pixels,  &test_pixels_normalize, "t10k-images-idx3-ubyte", 0);
    read_labels(&test_labels,  "t10k-labels-idx1-ubyte");

    iters_num = 10000;

    return 0;
}
