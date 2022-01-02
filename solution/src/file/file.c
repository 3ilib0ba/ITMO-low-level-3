#include "file/file_io.h"

bool open_file(FILE** file, const char *name, const char *mode) {
    *file = fopen(name, mode);
    return *file != NULL;
}

bool close_file(FILE * const *file) {
    return !fclose(*file);
}
