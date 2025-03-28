#include <stdbool.h>
#include <stdlib.h>

#include "../error/error.h"

bool check_string_malloc(char *string) {
    if (string == NULL) {
        error(-1, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    return true;
}
