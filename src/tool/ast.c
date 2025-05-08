#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "ast.h"
#include "utils/utils.h"

const char *EXPRESSION = "Expression";

void define_ast(char *output_dir, char *file_name, size_t definitions_length, char *definitions[definitions_length]) {
    size_t path_length = strlen(output_dir) + strlen(file_name) + 4; // +4 = folder separator, file extension and null terminator
    char *header_path = (char *)check_malloc(malloc(path_length * sizeof(char)));

    snprintf(header_path, path_length, "%s/%s.h", output_dir, file_name);

    printf("%s\n", header_path);

    create_directory(output_dir);

    char *mode = "w";
    FILE *header_file_p = fopen(header_path, mode);

    if (header_file_p == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // header
    fprintf_ln(header_file_p, "#ifndef EXPRESSION_H");
    fprintf_ln(header_file_p, "#define EXPRESSION_H");

    fprintf_ln(header_file_p, "#include \"../src/token/token.h\"");
    fprintf_ln(header_file_p, "#include \"../src/tool/py_type/py_type.h\"");
    fprintf_ln(header_file_p, "");

    fprintf_ln(header_file_p, "typedef struct %s %s;", EXPRESSION, EXPRESSION);
    fprintf_ln(header_file_p, "typedef struct %s {", EXPRESSION);
    fprintf_ln(header_file_p, "\tunion {");

    // ast structs
    for (unsigned int i = 0; i < definitions_length; i++) {
        char *definition = strdup(definitions[i]);
        char *union_name = strtok(definition, " :");
        char *fields = strtok(NULL, ":");
        define_expression(header_file_p, union_name, fields);

        free(definition);
    }

    fprintf_ln(header_file_p, "\t};");
    fprintf_ln(header_file_p, "} %s;", EXPRESSION);
    fprintf_ln(header_file_p, "");

    fprintf_ln(header_file_p, "#endif");

    fclose(header_file_p);

    free(header_path);
}

void define_expression(FILE *header_file_p, char *union_name, char *fields) {
    fprintf_ln(header_file_p, "\t\tstruct {");

    char *save_field_ptr;
    char *field = strtok_r(fields, ",", &save_field_ptr);

    for (; field != NULL; field = strtok_r(NULL, ",", &save_field_ptr)) {

        char *member = strdup(field);
        char *type = strtok(member, " ");
        char *identifier = strtok(NULL, " ");

        bool is_identifier_pointer = !strcmp(type, EXPRESSION);

        if (is_identifier_pointer) {
            char *identifier_pointer = check_malloc(malloc(strlen(identifier) + 2));
            identifier_pointer = concat_str("*", identifier);
            fprintf_ln(header_file_p, "\t\t\t%s %s;", type, identifier_pointer);

            free(identifier_pointer);
        }
        else {
            fprintf_ln(header_file_p, "\t\t\t%s %s;", type, identifier);
        }

        free(member);
    }

    fprintf_ln(header_file_p, "\t\t} %s;", union_name);
}
