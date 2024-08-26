#include "s21_matrix.h"

#include "help_functions.h"
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int result_create = OK;
  if (result == NULL || columns < 1 || rows < 1) {
    result_create = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          result_create = INCORRECT_MATRIX;
          break;
        }
      }
    } else {
      result_create = INCORRECT_MATRIX;
    }
  }
  return result_create;
}
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result_eq = SUCCESS;
  if (if_valid(A) && if_valid(B)) {
    for (int i = 0; i < A->rows && result_eq; i++) {
      for (int j = 0; j < A->columns && result_eq; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1.0E-7) {
          result_eq = FAILURE;
        }
      }
    }
  }
  return result_eq;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_sum = OK;
  if (if_valid(A) == SUCCESS && if_valid(B) == SUCCESS && result != NULL) {
    if (size_check(A, B) == SUCCESS) {
      if (s21_create_matrix(A->rows, A->columns, result) == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }

      } else {
        result_sum = INCORRECT_MATRIX;
      }

    } else {
      result_sum = CALCULATION_ERROR;
    }
  } else {
    result_sum = INCORRECT_MATRIX;
  }
  return result_sum;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_sub = OK;
  if (if_valid(A) == SUCCESS && if_valid(B) == SUCCESS && result != NULL) {
    if (size_check(A, B) == SUCCESS) {
      if (s21_create_matrix(A->rows, A->columns, result) == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }

      } else {
        result_sub = INCORRECT_MATRIX;
      }

    } else {
      result_sub = CALCULATION_ERROR;
    }
  } else {
    result_sub = INCORRECT_MATRIX;
  }
  return result_sub;
}
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int result_mult_number = OK;
  if (if_valid(A) == SUCCESS && result != NULL) {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }

    } else {
      result_mult_number = INCORRECT_MATRIX;
    }
  } else {
    result_mult_number = INCORRECT_MATRIX;
  }
  return result_mult_number;
}
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_mult_matrix = OK;
  if (if_valid(A) == SUCCESS && if_valid(B) == SUCCESS && result != NULL) {
    if (size_check_mult(A, B) == SUCCESS) {
      if (s21_create_matrix(A->rows, B->columns, result) == OK) {
        int res;
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            res = 0;
            for (int k = 0; k < B->rows; k++) {
              res += A->matrix[i][k] * B->matrix[k][j];
            }
            result->matrix[i][j] = res;
          }
        }

      } else {
        result_mult_matrix = INCORRECT_MATRIX;
      }

    } else {
      result_mult_matrix = CALCULATION_ERROR;
    }
  } else {
    result_mult_matrix = INCORRECT_MATRIX;
  }
  return result_mult_matrix;
}
int s21_transpose(matrix_t *A, matrix_t *result) {
  int result_transpose = OK;
  if (if_valid(A) == SUCCESS && result != NULL) {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      result_transpose = INCORRECT_MATRIX;
    }
  } else {
    result_transpose = INCORRECT_MATRIX;
  }
  return result_transpose;
}
int s21_determinant(matrix_t *A, double *result) {
  int result_determinant = OK;
  if (if_valid(A) == SUCCESS) {
    if (if_square_matrix(A) == SUCCESS) {
      if (A->columns == 1) {
        *result = A->matrix[0][0];
      } else if (A->columns == 2) {
        *result = (A->matrix[0][0] * A->matrix[1][1]) -
                  (A->matrix[1][0] * A->matrix[0][1]);
      } else {
        *result = 0;
        int sign = 1;
        for (int i = 0; i < A->columns; i++) {
          matrix_t minor = {0};
          s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
          create_minor_matrix(0, i, A, &minor);
          double minor_det;
          s21_determinant(&minor, &minor_det);
          *result += sign * A->matrix[0][i] * minor_det;
          sign *= -1;
          s21_remove_matrix(&minor);
        }
      }
    } else {
      result_determinant = CALCULATION_ERROR;
    }
  } else {
    result_determinant = INCORRECT_MATRIX;
  }
  return result_determinant;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int result_compl = OK;
  if (if_valid(A) == SUCCESS && result != NULL) {
    if (if_square_matrix(A) == SUCCESS) {
      if (s21_create_matrix(A->rows, A->columns, result) == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t minor = {0};
            s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
            create_minor_matrix(i, j, A, &minor);
            matrix_t buf_matrix = minor;
            double det;
            s21_determinant(&buf_matrix, &det);
            if ((i + j) % 2 == 0) {
              result->matrix[i][j] = det;
            } else {
              result->matrix[i][j] = -det;
            }
            s21_remove_matrix(&minor);
          }
        }
      } else {
        result_compl = INCORRECT_MATRIX;
      }
    } else {
      result_compl = CALCULATION_ERROR;
    }
  } else {
    result_compl = INCORRECT_MATRIX;
  }
  return result_compl;
}
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int result_inverse = OK;
  if (if_valid(A) == SUCCESS && result != NULL) {
    if (if_square_matrix(A) == SUCCESS) {
      double det_A;
      s21_determinant(A, &det_A);
      if (det_A != 0) {
        matrix_t compl_matrix = {0};
        s21_calc_complements(A, &compl_matrix);
        matrix_t transp_compl_matrix = {0};
        s21_transpose(&compl_matrix, &transp_compl_matrix);
        s21_mult_number(&transp_compl_matrix, 1 / det_A, result);

        s21_remove_matrix(&compl_matrix);
        s21_remove_matrix(&transp_compl_matrix);

      } else {
        result_inverse = CALCULATION_ERROR;
      }
    } else {
      result_inverse = CALCULATION_ERROR;
    }
  } else {
    result_inverse = INCORRECT_MATRIX;
  }
  return result_inverse;
}