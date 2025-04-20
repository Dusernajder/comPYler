#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdio.h>

#include "token/token.h"

typedef struct Expression Expression;

typedef struct Expression {
    Expression *left_p;
    Token operator_;
    Expression *right_p;
} Expression;

void define_ast(char *output_dir, char *file_name, size_t definitions_length, char *definitions[definitions_length]);
void define_struct(FILE *header_file_p, char *struct_name, char *field_names);
void fprintf_ln(FILE *file, const char *format, ...);

#endif
