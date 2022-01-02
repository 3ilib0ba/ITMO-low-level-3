#include "image/rotate_image.h"

#include <malloc.h>


static void update_image(struct image* output, struct image const* source, int i, int j) {
	output->pixels[i * output->width + j] =  (source->pixels[(source->height - 1 - j) * source->width + i]);
}

struct image image_create(size_t width, size_t height) {
    struct image output = {0};
    output.width = width;
    output.height = height;
    output.pixels = malloc(width * height * sizeof(struct pixel));
    return output;
}

struct image rotate(struct image const* source ) {
    struct image output = image_create(source->height, source->width);
    for (size_t i = 0; i < source->width; i++) {
        for (size_t j = 0; j < source->height; j++) {
            update_image(&output, source, i, j);
        }
    }
    return output;
}

void image_free(struct image img) {
    free(img.pixels);
}
