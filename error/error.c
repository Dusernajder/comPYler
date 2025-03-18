#include <stdbool.h>
#include <stdio.h>

#include "error.h"

bool hadError = false;

void error(int line, char *message) {
    report(line, "", message);
}

void report(int line, char *where, char *message) {
    printf("[Line \"%d\"] Error %s: %s", line, where, message);
    hadError = true;
}
