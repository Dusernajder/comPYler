#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct Member {
    char *type;
    char *identifier;
} Member;

typedef struct Definition {
    char *expression_type;
    size_t members_count;
    Member *members;
} Definition;

void define_ast(const char *output_dir, const char *file_name, const size_t definitions_length, const char *node_definitions[definitions_length]);
void write_expression_type(FILE *header_file_p, const size_t definitions_length, const Definition definitions[definitions_length]);
void write_expression(FILE *header_file_p, const size_t definitions_length, const Definition definitions[definitions_length]);
void create_definitions(const size_t definitions_length, const char *node_definitions[definitions_length], Definition out_definitions[definitions_length]);
void free_definitons(const size_t definitions_length, Definition definitions[definitions_length]);
FILE *create_header_file(const char *output_dir, const char *file_name);

#endif
