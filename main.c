#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error/error.h"
#include "scanner/scanner.h"
#include "tokenizer/tokenizer.h"

extern bool hadError;

void runFile(char *);
void runPrompt();
void run(char *);

void run(char *source) {
    if (hadError) {
        exit(EXIT_FAILURE);
    }

    TokenType tokens[256];
    scanTokens(source, tokens);
}

void runFile(char *path) {
    printf("Attempting to open: '%s'\n", path);

    char *mode = "r";
    FILE *file_p = fopen(path, mode);
    char line[256];

    if (file_p == NULL) {
        size_t errorMessageSize = 17 + strlen(path);
        char *errorMessage = malloc(errorMessageSize);
        snprintf(errorMessage, errorMessageSize, "File not found: %s", path);
        report(-1, path, "File not found");
    }

    for (size_t i = 0; fscanf(file_p, "%s", line) != EOF; i++) {
        printf("\n%lu. line: %s\n", i, line);
        run(line);
    }

    /*while (fgets(line, sizeof(line), file_p) != NULL) {*/
    /*    puts(line);*/
    /*    run(line);*/
    /*}*/

    fclose(file_p);
}

void runPrompt() {
    for (;;) {
        char *line = malloc(256);
        printf("> ");
        scanf("%s", line);

        int c = 2;
        bool val = strcmp(line, "\0");

        if (!strcmp(line, "\0")) {
            printf("%d", val);
            puts(line);
            break;
        }

        run(line);

        free(line);
    }
}

int main(int argc, char *argv[argc + 1]) {
    if (argc > 2) {
        exit(EXIT_FAILURE);
    }
    else if (argc == 1) {
        char *path = "/Volumes/SSD/projects/c/comPYler/script.py";
        /*char *path = argv[1];*/
        runFile(path);
    }
    else {
        runPrompt();
    }

    return EXIT_SUCCESS;
}
