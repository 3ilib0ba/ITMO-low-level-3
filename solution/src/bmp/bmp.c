#include "bmp/bmp_header.h"
#include "bmp/bmp_io.h"
#include "image/rotate_image.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#define BMP_TYPE 0x4D42
#define BMP_PLANES 1
#define BMP_HEADER_SIZE 40

static enum read_status read_header(FILE* in, struct bmp_header* header) {
	if (fseek(in, 0, SEEK_END) != 0) {
		return READ_ERROR;
	}
    size_t size = ftell(in);
    if (size < sizeof(struct bmp_header)) {
		return READ_INVALID_HEADER; 
	}

    rewind(in);
    if (fread(header, sizeof(struct bmp_header), 1, in) != 1) {
		return READ_ERROR;
	}
    return READ_OK;
}

static enum read_status read_pixels(struct image *img, FILE* in, uint8_t padding) {
    struct image copyImage = image_create(img->width, img->height);
	size_t width = img->width;
    size_t height = img->height;
    struct pixel* pixels = copyImage.pixels;
	for (size_t i = 0; i < height; i++) {
		if (fread(pixels + i * width, sizeof(struct pixel), width, in) != width) {
			return READ_ERROR;
		}
		if (fseek(in, padding, SEEK_CUR) != 0) {
			return READ_ERROR;
		}
	}
    (*img).pixels = pixels;
	return READ_OK;
}



static uint8_t get_padding(uint32_t width) {
	return width % 4;
}



enum read_status from_bmp(FILE* in, struct image *img) {
	struct bmp_header header = {0};
	enum read_status st = read_header(in, &header);
	if (st == READ_INVALID_HEADER || st == READ_ERROR) {
		return READ_INVALID_SIGNATURE;
	}
	img->width = header.biWidth;
	img->height = header.biHeight;
	return read_pixels(img, in, get_padding(header.biWidth));
}



static struct bmp_header create_header(struct image* img) {
	uint32_t img_size = (sizeof(struct pixel) * img->width + get_padding(img->width)) * img->height;
	struct bmp_header header = {
		.bfType = BMP_TYPE,
		.bfileSize = sizeof(struct bmp_header) + img_size,
		.bfReserved = 0,
		.bOffBits = sizeof(struct bmp_header),
		.biSize = BMP_HEADER_SIZE,
		.biWidth = img->width,
		.biHeight = img->height,
		.biPlanes = BMP_PLANES,
		.biBitCount = 24,
		.biCompression = BI_RGB,
		.biSizeImage = img_size,
		.biXPelsPerMeter = 0,
		.biYPelsPerMeter = 0,
		.biClrUsed = 0,
		.biClrImportant = 0,

	};
	return header;
}



static enum write_status write_image(struct image *img, FILE *out, uint8_t padding) {
    const size_t width = img->width;
    const size_t height = img->height;
    const uint64_t zero = 0;
	uint64_t cnt = 0;
	for (size_t i = 0; i < height; ++i) {
		cnt += fwrite(img->pixels + i * width, sizeof (struct pixel), width, out);
		if (fwrite(&zero, 1, padding, out) != padding) {
			return WRITE_ERROR;
		}
	}
	if (cnt == height * width) {
		return WRITE_OK;
	}
	return WRITE_ERROR;
}




enum write_status to_bmp(FILE* out, struct image *img) {
	struct bmp_header header = create_header(img);
	if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1) {
		return WRITE_ERROR;
	}
	uint8_t padding = get_padding(header.biWidth);
	return write_image(img, out, padding);	
}
