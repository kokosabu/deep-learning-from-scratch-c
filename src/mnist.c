#include <mnist.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

typedef struct tagIMAGEINFO {
    uint32_t fileSize;
    int32_t  width;
    int32_t  height;
} IMAGEINFO;

typedef struct tagBITMAPFILEHEADER {
  uint16_t bfType;
  uint32_t bfSize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  uint32_t biSize;
  int32_t  biWidth;
  int32_t  biHeight;
  uint16_t biPlanes;
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t  biXPelsPerMeter;
  int32_t  biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBTRIPLE { 
  uint16_t rgbtBlue; 
  uint16_t rgbtGreen; 
  uint16_t rgbtRed;

  uint16_t rgbtAlpha; 
} RGBTRIPLE;

uint32_t read_4bytes(FILE *input)
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

void encode_bitmap(FILE *output, IMAGEINFO *image_info, RGBTRIPLE ***output_image_data)
{
    int i;
    int j;
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    uint32_t cal;
    uint8_t write_data;
    uint8_t dummy;

    file_header.bfType      = ('M' << 8) | 'B';
    file_header.bfSize      = image_info->fileSize;
    file_header.bfReserved1 = 0;
    file_header.bfReserved2 = 0;
    file_header.bfOffBits   = 14 + 40;

    fwrite(&file_header.bfType, 2, 1, output);
    fwrite(&file_header.bfSize, 4, 1, output);
    fwrite(&file_header.bfReserved1, 2, 1, output);
    fwrite(&file_header.bfReserved2, 2, 1, output);
    fwrite(&file_header.bfOffBits, 4, 1, output);

    info_header.biSize          = 40;
    info_header.biWidth         = image_info->width;
    info_header.biHeight        = image_info->height;
    info_header.biPlanes        = 1;
    info_header.biBitCount      = 24;
    info_header.biCompression   = 0;
    info_header.biSizeImage     = image_info->width * image_info->height * 3;
    info_header.biXPelsPerMeter = 0;
    info_header.biYPelsPerMeter = 0;
    info_header.biClrUsed       = 0;
    info_header.biClrImportant  = 0;
    fwrite(&info_header.biSize,          4, 1, output);
    fwrite(&info_header.biWidth,         4, 1, output);
    fwrite(&info_header.biHeight,        4, 1, output);
    fwrite(&info_header.biPlanes,        2, 1, output);
    fwrite(&info_header.biBitCount,      2, 1, output);
    fwrite(&info_header.biCompression,   4, 1, output);
    fwrite(&info_header.biSizeImage,     4, 1, output);
    fwrite(&info_header.biXPelsPerMeter, 4, 1, output);
    fwrite(&info_header.biYPelsPerMeter, 4, 1, output);
    fwrite(&info_header.biClrUsed,       4, 1, output);
    fwrite(&info_header.biClrImportant,  4, 1, output);

    fseek(output, file_header.bfOffBits, SEEK_SET);

    for(i = info_header.biHeight-1; i >= 0; i--) {
        for(j = 0; j < info_header.biWidth; j++) {
            cal = ((uint32_t)(*output_image_data)[i][j].rgbtBlue * ((*output_image_data)[i][j].rgbtAlpha) / 255) + (255 * ((uint32_t)255 - (*output_image_data)[i][j].rgbtAlpha) / 255);
            if(cal > 255) {
                write_data = 255;
            } else {
                write_data = cal;
            }
            fwrite(&write_data, 1, 1, output);

            cal = ((uint32_t)(*output_image_data)[i][j].rgbtGreen * ((*output_image_data)[i][j].rgbtAlpha) / 255) + (255 * ((uint32_t)255 - (*output_image_data)[i][j].rgbtAlpha) / 255);
            if(cal > 255) {
                write_data = 255;
            } else {
                write_data = cal;
            }
            fwrite(&write_data, 1, 1, output);

            cal = ((uint32_t)(*output_image_data)[i][j].rgbtRed * ((*output_image_data)[i][j].rgbtAlpha) / 255) + (255 * ((uint32_t)255 - (*output_image_data)[i][j].rgbtAlpha) / 255);
            if(cal > 255) {
                write_data = 255;
            } else {
                write_data = cal;
            }
            fwrite(&write_data, 1, 1, output);
        }
        if(((3*info_header.biWidth)%4) != 0) {
            dummy = 0;
            fwrite(&dummy, 1, 4 - ((3*info_header.biWidth)%4), output);
        }
    }
}

int main()
{
    FILE *train_images;
    FILE *train_labels;
    FILE *bitmap;
    uint32_t magic_number;
    uint32_t images;
    uint32_t rows;
    uint32_t columns;
    uint32_t items;
    uint8_t **pixels;
    uint8_t label;
    IMAGEINFO image_info;
    RGBTRIPLE **output_image_data;
    int i;
    int j;
    int k;

    // @build folder
    train_images = fopen("../dataset/train-images-idx3-ubyte", "r");
    train_labels = fopen("../dataset/train-labels-idx1-ubyte", "r");

    bitmap = fopen("./test.bmp", "w");

    magic_number = read_4bytes(train_images);
    assert(magic_number == 0x00000803);
    images = read_4bytes(train_images);
    assert(images == 60000);
    rows = read_4bytes(train_images);
    assert(rows == 28);
    columns = read_4bytes(train_images);
    assert(columns == 28);

    output_image_data = (RGBTRIPLE **)malloc(sizeof(RGBTRIPLE *) * columns);
    for(i = 0; i < columns; i++) {
        output_image_data[i] = (RGBTRIPLE *)malloc(sizeof(RGBTRIPLE) * rows);
    }

    pixels = (uint8_t **)malloc(sizeof(uint8_t *) * images);
    for(i = 0; i < images; i++) {
        pixels[i] = (uint8_t *)malloc(sizeof(uint8_t) * (rows*columns));
        fread(pixels[i], 1, rows*columns, train_images);
    }

    for(j = 0; j < columns; j++) {
        for(k = 0; k < rows; k++) {
            output_image_data[j][k].rgbtRed   = pixels[1][(j*rows) + k];
            output_image_data[j][k].rgbtGreen = pixels[1][(j*rows) + k];
            output_image_data[j][k].rgbtBlue  = pixels[1][(j*rows) + k];
            output_image_data[j][k].rgbtAlpha = 255;
        }
    }

    image_info.fileSize = rows * columns * 3 + 54;
    image_info.height = columns;
    image_info.width = rows;
    encode_bitmap(bitmap, &image_info, &output_image_data);

    magic_number = read_4bytes(train_labels);
    assert(magic_number == 0x00000801);
    items = read_4bytes(train_labels);
    assert(items == 60000);

    fread(&label, 1, 1, train_labels);
    printf("%d\n", label);

    fclose(train_images);
    fclose(train_labels);
    fclose(bitmap);

    return 0;
}
