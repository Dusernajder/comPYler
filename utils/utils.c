#include <stdbool.h>
#include <stdlib.h>

#include "../error/error.h"

void *check_malloc(void *ptr) {
    if (ptr == NULL) {
        error(-1, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    return ptr;
}
