#include <mnist.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static uint32_t read_4bytes(FILE *input)
{
    uint8_t byte;
    uint32_t result;

    fread(&byte, 1, 1, input);
    result = byte;
    fread(&byte, 1, 1, input);
    result = (result << 8) | byte;
    fread(&byte, 1, 1, input);
    result = (result << 8) | byte;
    fread(&byte, 1, 1, input);
    result = (result << 8) | byte;

    return result;
}

void read_labels(uint8_t **labels, char *filename)
{
    FILE *labels_data;
    uint32_t magic_number;
    uint32_t items;

    labels_data = fopen(filename, "r");

    magic_number = read_4bytes(labels_data);
    assert(magic_number == 0x00000801);
    items = read_4bytes(labels_data);

    *labels = (uint8_t *)malloc(sizeof(uint8_t) * items);

    fread((*labels), 1, items, labels_data);

    fclose(labels_data);
}

void read_images(uint8_t ***pixels, double ***pixels_normalize, char *filename, int flag)
{
    FILE *images_data;
    uint32_t magic_number;
    uint32_t images;
    uint32_t rows;
    uint32_t columns;
    int i;
    int j;

    images_data = fopen(filename, "r");

    magic_number = read_4bytes(images_data);
    assert(magic_number == 0x00000803);
    images = read_4bytes(images_data);
    //assert(images == 60000);
    rows = read_4bytes(images_data);
    assert(rows == 28);
    columns = read_4bytes(images_data);
    assert(columns == 28);

    *pixels = (uint8_t **)malloc(sizeof(uint8_t *) * images);
    for(i = 0; i < images; i++) {
        (*pixels)[i] = (uint8_t *)malloc(sizeof(uint8_t) * (rows*columns));
        fread((*pixels)[i], 1, rows*columns, images_data);
    }

    if(flag == 1) {
        *pixels_normalize = (double **)malloc(sizeof(double *) * images);
        for(i = 0; i < images; i++) {
            (*pixels_normalize)[i] = (double *)malloc(sizeof(double) * (rows*columns));
            for(j = 0; j < (rows*columns); j++) {
                (*pixels_normalize)[i][j] = (double)(*pixels)[i][j] / (double)255;
            }
        }
    }

    fclose(images_data);
}

