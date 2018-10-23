#ifndef __MNIST_H

#include <stdint.h>

void read_labels(uint8_t **labels, char *filename);
void read_images(uint8_t ***pixels, double ***pixels_normalize, char *filename, int flag);

#endif /* __MNIST_H */
