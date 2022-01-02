#include "image/rotate_image.h"
#include "bmp/bmp_io.h"
#include "file/file_io.h"

#include <assert.h>
#include <malloc.h>

int main(int args, char **argv) {

    if (args != 3) {
        printf("Not enough arguments");
        return 1;
    }
    char const *file_input = argv[1];
    char const *file_output = argv[2];
    FILE* input = NULL;
    FILE* output = NULL;

    if (!open_file(&input, file_input, "rb")) {
        printf("Error! Can't read the input file");
        return 1;
    }
    if (!open_file(&output, file_output, "wb")) {
        printf("Error! Can't (over-)write the output file");
        return 1;
    }

    struct image image = {0};
    if (from_bmp(input, &image) != READ_OK) {
        printf("Error! Can't read the input file");
        close_file(&input);
        close_file(&output);
        image_free(image);
        return 1;
    }
    struct image rotated_image = rotate(&image);
    if (to_bmp(output, &rotated_image) != WRITE_OK) {
        printf("Error! Can't write to the output file");
        close_file(&input);
        close_file(&output);
        image_free(image);
        image_free(rotated_image);
        return 1;
    }
    if (!close_file(&input) || !close_file(&output)) {
        printf("Error! Can't close the files");
        return 1;
    }
    image_free(image);
    image_free(rotated_image);

    return 0;
}
