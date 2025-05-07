#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "ast.h"
#include "utils/utils.h"

void define_ast(char *output_dir, char *file_name, size_t definitions_length, char *definitions[definitions_length]) {
    size_t path_length = strlen(output_dir) + strlen(file_name) + 4; // +4 = folder separator, file extension and null terminator
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
    fprintf_ln(header_file_p, "#include \"../src/tool/py_type/py_type.h\"");
    fprintf_ln(header_file_p, "");

    fprintf_ln(header_file_p, "typedef struct Expression Expression;");

    fprintf_ln(header_file_p, "typedef struct Expression {");

    fprintf_ln(header_file_p, "\tunion {");

    // ast structs
    for (unsigned int i = 0; i < definitions_length; i++) {
        char *definition = strdup(definitions[i]);
        char *struct_name = strtok(definition, " :");
        char *field_names = strtok(NULL, ":");
        define_expression(header_file_p, struct_name, field_names);

        free(definition);
    }

    fprintf_ln(header_file_p, "\t};");
    fprintf_ln(header_file_p, "} Expression;");

    fprintf_ln(header_file_p, "");

    fprintf_ln(header_file_p, "#endif");


    fclose(header_file_p);

    free(header_path);
}

void define_expression(FILE *header_file_p, char *struct_name, char *field_names) {
    fprintf_ln(header_file_p, "\t\tstruct {");

    char *save_field_ptr;
    char *field = strtok_r(field_names, ",", &save_field_ptr);

    while (field != NULL) {
        char *member = strdup(field);
        char *type = strtok(member, " ");
        char *identifier = strtok(NULL, " ");
        
        char *identifier_pointer = check_malloc(malloc(sizeof(identifier) + 2));

        bool is_identifier_pointer = !strcmp(type, "Expression");

        if (is_identifier_pointer){
            identifier_pointer = concat_str("*", identifier);
        }

        char *result = is_identifier_pointer ? identifier_pointer : identifier;
        fprintf_ln(header_file_p, "\t\t\t%s %s;", type, result);

        field = strtok_r(NULL, ",", &save_field_ptr);

        free(identifier_pointer);
        free(member);
    }

    fprintf_ln(header_file_p, "\t\t} %s;", struct_name);

    free(field);
}

void fprintf_ln(FILE *file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);
    fprintf(file, "\n");
}
