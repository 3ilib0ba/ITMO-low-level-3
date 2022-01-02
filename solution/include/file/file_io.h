#include <stdbool.h>
#include <stdio.h>

bool open_file(FILE** file, const char *name, const char *mode);

bool close_file(FILE* const *file);
