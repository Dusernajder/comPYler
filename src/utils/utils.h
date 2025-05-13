#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void *check_malloc(void *ptr);
bool is_directory_exists(const char *directory);
void create_directory(const char *directory);
char *concat_str(const char *s1, const char *s2);
void fprintf_ln(FILE *file, const char *format, ...);
