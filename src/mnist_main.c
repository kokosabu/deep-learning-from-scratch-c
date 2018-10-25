#include <mnist.h>
#include <stdint.h>
#include <stdio.h>

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
    uint8_t **train_pixels;
    uint8_t *train_labels;
    uint8_t **test_pixels;
    uint8_t *test_labels;
    //double **train_pixels_normalize;
    double **test_pixels_normalize;
#if 0
    FILE *bitmap;
    IMAGEINFO image_info;
    RGBTRIPLE **output_image_data;
    char filename[255];
#endif
    uint32_t images;
    uint32_t rows;
    uint32_t columns;
    int i;
    int j;
    int k;

    read_images(&train_pixels, NULL, "train-images-idx3-ubyte", 0);
    read_labels(&train_labels, "train-labels-idx1-ubyte");
    read_images(&test_pixels,  &test_pixels_normalize, "t10k-images-idx3-ubyte", 1);
    read_labels(&test_labels,  "t10k-labels-idx1-ubyte");

    images  = 60000;
    rows    = 28;
    columns = 28;

    for(i = 0; i < 1; i++) {
        for(j = 0; j < columns; j++) {
            for(k = 0; k < rows; k++) {
                printf("%4d ", test_pixels[0][(j*rows)+k]);
            }
            printf("\n");
        }
    }
    for(i = 0; i < 1; i++) {
        for(j = 0; j < columns; j++) {
            for(k = 0; k < rows; k++) {
                printf("%.2f ", (double)test_pixels[0][(j*rows)+k] / (double)255);
            }
            printf("\n");
        }
    }

#if 0
    output_image_data = (RGBTRIPLE **)malloc(sizeof(RGBTRIPLE *) * columns);
    for(i = 0; i < columns; i++) {
        output_image_data[i] = (RGBTRIPLE *)malloc(sizeof(RGBTRIPLE) * rows);
    }
    image_info.fileSize = rows * columns * 3 + 54;
    image_info.height = columns;
    image_info.width = rows;

    for(i = 0; i < images; i++) {
        sprintf(filename, "./test%05d.bmp", i);
        bitmap = fopen(filename, "w");
        for(j = 0; j < columns; j++) {
            for(k = 0; k < rows; k++) {
                output_image_data[j][k].rgbtRed   = pixels[i][(j*rows) + k];
                output_image_data[j][k].rgbtGreen = pixels[i][(j*rows) + k];
                output_image_data[j][k].rgbtBlue  = pixels[i][(j*rows) + k];
                output_image_data[j][k].rgbtAlpha = 255;
            }
        }
        encode_bitmap(bitmap, &image_info, &output_image_data);
        fclose(bitmap);
    }
#endif

    return 0;
}
