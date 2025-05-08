#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdio.h>

void define_ast(char *output_dir, char *file_name, size_t definitions_length, char *definitions[definitions_length]);
void define_expression(FILE *header_file_p, char *struct_name, char *field_names);

#endif
