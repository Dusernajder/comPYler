#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "utils/utils.h"

const char *EXPRESSION = "Expression";

void define_ast(const char *output_dir, const char *file_name, const size_t node_signatures_length, const char *node_signatures[node_signatures_length]) {
    FILE *header_file_p = create_header_file(output_dir, file_name);
    Definition *definitions = check_malloc(malloc(sizeof(Definition) * node_signatures_length));

    fprintf_ln(header_file_p, "#ifndef %s_H", EXPRESSION);
    fprintf_ln(header_file_p, "#define %s_H", EXPRESSION);

    fprintf_ln(header_file_p, "#include \"../src/token/token.h\"");
    fprintf_ln(header_file_p, "#include \"../src/tool/py_type/py_type.h\"");
    fprintf_ln(header_file_p, "");

    create_definitions(node_signatures_length, node_signatures, definitions);
    write_expression_type(header_file_p, node_signatures_length, definitions);

    fprintf_ln(header_file_p, "");
    fprintf_ln(header_file_p, "typedef struct %s %s;", EXPRESSION, EXPRESSION);
    fprintf_ln(header_file_p, "");
    fprintf_ln(header_file_p, "typedef struct %s {", EXPRESSION);
    fprintf_ln(header_file_p, "\tExpressionType expression_type;");

    write_expression(header_file_p, node_signatures_length, definitions);

    fprintf_ln(header_file_p, "} %s;", EXPRESSION);
    fprintf_ln(header_file_p, "");

    fprintf_ln(header_file_p, "#endif");

    fclose(header_file_p);
    free_definitons(node_signatures_length, definitions);
}

void write_expression_type(FILE *header_file_p, const size_t definitions_length, const Definition definitions[definitions_length]) {
    fprintf_ln(header_file_p, "typedef enum {");

    for (unsigned int i = 0; i < definitions_length; i++) {
        fprintf_ln(header_file_p, "\t%s,", definitions[i].expression_type);
    }

    fprintf_ln(header_file_p, "} ExpressionType;");
}

void write_expression(FILE *header_file_p, const size_t definitions_length, const Definition definitions[definitions_length]) {
    fprintf_ln(header_file_p, "\tunion {");

    for (unsigned int i = 0; i < definitions_length; i++) {
        fprintf_ln(header_file_p, "\t\tstruct {");

        for (unsigned int j = 0; j < definitions[i].members_count; j++) {
            Member *current_member_p = &definitions[i].members[j];

            if (!strcmp(current_member_p->type, EXPRESSION)) {
                fprintf_ln(header_file_p, "\t\t\t%s %s;", current_member_p->type, concat_str("*", current_member_p->identifier));
            }
            else {
                fprintf_ln(header_file_p, "\t\t\t%s %s;", current_member_p->type, current_member_p->identifier);
            }
        }

        fprintf_ln(header_file_p, "\t\t} %s;", definitions[i].expression_type);
    }

    fprintf_ln(header_file_p, "\t};");
}

void create_definitions(const size_t definitions_length, const char *node_definitions[definitions_length], Definition out_definitions[definitions_length]) {
    for (unsigned int i = 0; i < definitions_length; i++) {
        char *definition = strdup(node_definitions[i]);

        char *expression_type = strdup(strtok(definition, " :"));
        out_definitions[i].expression_type = expression_type;

        char *members = strtok(NULL, ":");
        char *member_parser_pointer;
        char *member = strtok_r(members, ",", &member_parser_pointer);
        size_t members_count = 0;

        out_definitions[i].members = NULL;

        for (; member != NULL; member = strtok_r(NULL, ",", &member_parser_pointer)) {
            out_definitions[i].members = check_malloc(realloc(out_definitions[i].members, sizeof(Member) * (members_count + 1)));

            char *type = strtok(member, " ");
            char *identifier = strtok(NULL, " ");

            out_definitions[i].members[members_count].type = strdup(type);
            out_definitions[i].members[members_count].identifier = strdup(identifier);

            members_count++;
        }

        out_definitions[i].members_count = members_count;

        free(definition);
    }
}

void free_definitons(const size_t definitions_length, Definition definitions[definitions_length]) {
    for (unsigned int i = 0; i < definitions_length; i++) {
        free(definitions[i].expression_type);
        for (unsigned int j = 0; j < definitions[i].members_count; j++) {
            free(definitions[i].members[j].type);
            free(definitions[i].members[j].identifier);
        }
        free(definitions[i].members);
    }
}

FILE *create_header_file(const char *output_dir, const char *file_name) {
    size_t path_length = strlen(output_dir) + strlen(file_name) + 4; // +4 = folder separator, file extension and null terminator

    char *header_path = (char *)check_malloc(malloc(path_length * sizeof(char)));
    snprintf(header_path, path_length, "%s/%s.h", output_dir, file_name);

    create_directory(output_dir);

    char *mode = "w";
    FILE *header_file_p = fopen(header_path, mode);

    if (header_file_p == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("File created: %s\n", header_path);

    return header_file_p;
}
