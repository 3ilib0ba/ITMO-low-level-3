#include "image.h"

struct image rotate(struct image const* source);
void image_free(struct image img);
struct image image_create(size_t width, size_t height);
