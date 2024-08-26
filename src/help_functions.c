#include "help_functions.h"

#include "s21_matrix.h"
int if_valid(matrix_t *A) {
  int result = FAILURE;
  if (A != NULL && A->columns > 0 && A->rows > 0 && A->matrix != NULL) {
    result = SUCCESS;
  }
  return result;
}
int size_check(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  if (A->columns == B->columns && A->rows == B->rows) {
    result = SUCCESS;
  }
  return result;
}
int size_check_mult(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  if (A->columns == B->rows && A->rows == B->columns) {
    result = SUCCESS;
  }
  return result;
}
void create_minor_matrix(int I, int J, matrix_t *A, matrix_t *minor) {
  int i_minor = 0;
  int j_minor = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i != I && j != J) {
        minor->matrix[i_minor][j_minor] = A->matrix[i][j];
        j_minor++;
        if (j_minor == A->columns - 1) {
          j_minor = 0;
          i_minor++;
        }
      }
    }
  }
}
int if_square_matrix(matrix_t *A) {
  int result = FAILURE;
  if (A->columns == A->rows) {
    result = SUCCESS;
  }
  return result;
}
// for tests
void initialization_matrix(double n, matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = n;
      }
    }
  }
}
void print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("%f ", A->matrix[i][j]);
    }
    printf("\n");
  }
}