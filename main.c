#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error/error.h"
#include "scanner/scanner.h"
#include "tokenizer/token.h"

extern bool hadError;

void run(char *);
void runFile(char *);
void runPrompt();

long getFileContentSize(FILE *);

void run(char *source) {
    Token tokens[256];
    scanTokens(source, tokens);

    if (hadError) {
        exit(EXIT_FAILURE);
    }
}

void runFile(char *path) {
    printf("Attempting to open: '%s'\n", path);

    char *mode = "r";
    FILE *file_p = fopen(path, mode);

    if (file_p == NULL) {
        size_t errorMessageSize = 17 + strlen(path);
        char *errorMessage = malloc(errorMessageSize);
        snprintf(errorMessage, errorMessageSize, "File not found: %s", path);
        report(-1, path, "File not found");

        exit(EXIT_FAILURE);
    }

    long fileContentSize = getFileContentSize(file_p);

    char *fileContent_p = malloc(fileContentSize);
    fread(fileContent_p, 1, fileContentSize, file_p);

    run(fileContent_p);

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

long getFileContentSize(FILE *file_p) {
    fseek(file_p, 0L, SEEK_END);
    long fileContentSize = ftell(file_p);
    fseek(file_p, 0L, SEEK_SET);

    return fileContentSize;
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
