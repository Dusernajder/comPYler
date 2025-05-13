#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "error/error.h"

void *check_malloc(void *ptr) {
    if (ptr == NULL) {
        error(-1, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

bool is_directory_exists(const char *directory) {
    struct stat st;
    return (stat(directory, &st) == 0) && S_ISDIR(st.st_mode);
}

void create_directory(const char *directory) {
    if (!is_directory_exists(directory)) {
        if (mkdir(directory, 0755) != 0) {
            perror("mkdir failed");
            exit(EXIT_FAILURE);
        }
    }
}

char *concat_str(const char *s1, const char *s2, ...) {
    char *result = malloc(sizeof(s1) + sizeof(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

void fprintf_ln(FILE *file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);
    fprintf(file, "\n");
}
