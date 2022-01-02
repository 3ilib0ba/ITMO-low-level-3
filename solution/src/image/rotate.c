#include "../../solution/include/image/rotate_image.h"

#include <malloc.h>

static void update_image(struct image* output, struct image const* source, int i, int j) {
	output->pixels[i * output->width + j] =  (source->pixels[(source->height - 1 - j) * source->width + i]);
}

struct image rotate(struct image const* source ) {
    struct image output = {0};
    output.width = source->height;
    output.height = source->width;
    output.pixels = malloc(sizeof(struct pixel) * source->width * source->height);
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
