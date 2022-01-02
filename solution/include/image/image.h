#include <stdint.h>
#include <stdio.h>

#pragma once
struct image {
    size_t width;
    size_t height;
    struct pixel* pixels;
};

struct pixel {
    uint8_t b, g, r;
};
