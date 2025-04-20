#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error/error.h"
#include "scanner/scanner.h"
#include "token/token.h"
#include "utils/utils.h"

extern bool had_error;

void run(char *);
void run_file(char *);
void run_prompt();
long get_file_conent_size(FILE *);

void run(char *source) {
    size_t capacity = 256;
    Token *tokens_buffer = malloc(sizeof(Token) * capacity);

    scanner_init(source);
    unsigned int tokens_length = 0;
    scan_tokens(tokens_buffer, &tokens_length);

    Token *tokens = realloc(tokens_buffer, tokens_length);

    /*for (unsigned int i = 0; i < 256; i++) {*/
    /*    Token token = tokens[i];*/
    /*    printf("%d\n", token.type);*/
    /*    if (token.type == EOF_){*/
    /*        printf("%d", i);*/
    /*    }*/
    /*}*/

    free(tokens);

    if (had_error) {
        exit(EXIT_FAILURE);
    }
}

void run_file(char *path) {
    printf("Attempting to open: '%s'\n", path);

    char *mode = "r";
    FILE *file_p = fopen(path, mode);

    if (file_p == NULL) {
        size_t error_message_size = 17 + strlen(path);
        char *error_message = check_malloc(malloc(error_message_size));
        snprintf(error_message, error_message_size, "File not found: %s", path);
        report(-1, path, "File not found");

        exit(EXIT_FAILURE);
    }

    long file_content_size = get_file_conent_size(file_p);
    char *fileContent_p = check_malloc(malloc(file_content_size));

    fread(fileContent_p, 1, file_content_size, file_p);

    run(fileContent_p);

    free(fileContent_p);
    fclose(file_p);
}

void run_prompt() {
    for (;;) {
        char *line = check_malloc(malloc(256));

        printf("> ");
        scanf("%s", line);

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

long get_file_conent_size(FILE *file_p) {
    fseek(file_p, 0L, SEEK_END);
    long file_content_size = ftell(file_p);
    fseek(file_p, 0L, SEEK_SET);

    return file_content_size;
}

int main(int argc, char *argv[argc + 1]) {
    if (argc > 2) {
        exit(EXIT_FAILURE);
    }
    else if (argc == 1) {
        char *path = "/Volumes/SSD/projects/c/comPYler/script.py";
        /*char *path = argv[1];*/
        run_file(path);
    }
    else {
        run_prompt();
    }

    return EXIT_SUCCESS;
}
