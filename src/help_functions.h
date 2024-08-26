#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "s21_matrix.h"

typedef struct matrix_struct matrix_t;
typedef struct matrix_struct matrix_t;
int if_valid(matrix_t *A);
int size_check(matrix_t *A, matrix_t *B);
int size_check_mult(matrix_t *A, matrix_t *B);
void create_minor_matrix(int I, int J, matrix_t *A, matrix_t *minor);
int if_square_matrix(matrix_t *A);
void initialization_matrix(double n, matrix_t *A);

void print_matrix(matrix_t *A);
#endif  // HELP_FUNCTIONS_H