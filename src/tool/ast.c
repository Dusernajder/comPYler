#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "ast.h"
#include "utils/utils.h"

void define_ast(char *output_dir, char *file_name, size_t members_length, char *definitions[members_length]) {
    size_t path_length = strlen(output_dir) + strlen(file_name) + 4; // +4 = folder separator, null terminator and file extension
    char *header_path = (char *)check_malloc(malloc(path_length * sizeof(char)));
    char *source_path = (char *)check_malloc(malloc(path_length * sizeof(char)));

    snprintf(header_path, path_length, "%s/%s.h", output_dir, file_name);
    snprintf(source_path, path_length, "%s/%s.c", output_dir, file_name);

    printf("%s\n", header_path);
    printf("%s\n", source_path);

    create_directory(output_dir);

    char *mode = "w";
    FILE *header_file_p = fopen(header_path, mode);
    FILE *source_file_p = fopen(source_path, mode);

    if (source_file_p == NULL || header_file_p == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // header
    fprintf_ln(header_file_p, "#ifndef EXPRESSION_H");
    fprintf_ln(header_file_p, "#define EXPRESSION_H");

    fprintf_ln(header_file_p, "#include \"../src/token/token.h\"");
    fprintf_ln(header_file_p, "#include \"../src/tool/ast.h\"");
    fprintf_ln(header_file_p, "#include \"../src/tool/py_type/py_type.h\"");
    fprintf_ln(header_file_p, "");

    // ast structs
    for (unsigned int i = 0; i < members_length; i++) {
        char *definition = strdup(definitions[i]);
        char *struct_name = strtok(definition, " :");
        char *field_names = strtok(NULL, ":");
        define_struct(header_file_p, struct_name, field_names);

        free(definition);
    }

    fprintf_ln(header_file_p, "#endif");

    // source
    fprintf_ln(source_file_p, "#include \"%s.h\"", file_name);

    fclose(header_file_p);
    fclose(source_file_p);

    free(header_path);
    free(source_path);
}

void define_struct(FILE *header_file_p, char *struct_name, char *field_names) {
    fprintf_ln(header_file_p, "typedef struct %s {", struct_name);

    char *save_field_ptr;
    char *field = strtok_r(field_names, ",", &save_field_ptr);

    while (field != NULL) {
        char *member = strdup(field);
        char *type = strtok(member, " ");
        char *identifier = strtok(NULL, " ");

        fprintf_ln(header_file_p, "\t%s %s;", type, identifier);

        field = strtok_r(NULL, ",", &save_field_ptr);

        free(member);
    }

    fprintf_ln(header_file_p, "} %s;", struct_name);
    fprintf_ln(header_file_p, "");

    free(field);
}

void fprintf_ln(FILE *file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);
    fprintf(file, "\n");
}
