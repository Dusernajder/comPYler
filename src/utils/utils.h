#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void *check_malloc(char *);
bool is_directory_exists(char *directory);
void create_directory(char *directory);
char *concat_str(const char *s1, const char *s2);
void fprintf_ln(FILE *file, const char *format, ...);
