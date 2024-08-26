#include "tests.h"

#include <check.h>

START_TEST(test_create_invalid_matrix) {
  matrix_t a = {0};
  ck_assert_int_eq(s21_create_matrix(0, 2, &a), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test_sum_diff_size) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  s21_create_matrix(2, 1, &b);
  initialization_matrix(2, &b);
  // s21_create_matrix(2, 2, &result);
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_invalid_matrix) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  s21_create_matrix(2, 0, &b);
  initialization_matrix(2, &b);
  // s21_create_matrix(2, 2, &result);
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_1) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  s21_create_matrix(2, 2, &b);
  initialization_matrix(1, &b);
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  initialization_matrix(3, &expected);
  s21_sum_matrix(&a, &b, &result);
  ck_assert_int_eq(!s21_eq_matrix(&result, &expected), OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sub_diff_size) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  s21_create_matrix(2, 1, &b);
  initialization_matrix(2, &b);
  // s21_create_matrix(2, 2, &result);
  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_invalid_matrix) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  s21_create_matrix(2, 0, &b);
  initialization_matrix(2, &b);
  // s21_create_matrix(2, 2, &result);
  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_1) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  s21_create_matrix(2, 2, &b);
  initialization_matrix(1, &b);
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  initialization_matrix(1, &expected);
  s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(!s21_eq_matrix(&result, &expected), OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_eq_matrix_1) {
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  s21_create_matrix(2, 2, &b);
  initialization_matrix(1, &b);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_mult_number_1) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 2, &a);
  initialization_matrix(2, &a);
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  initialization_matrix(6, &expected);
  s21_mult_number(&a, 3, &result);
  ck_assert_int_eq(!s21_eq_matrix(&result, &expected), OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_number_invalid_matrix) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 0, &a);
  initialization_matrix(2, &a);
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  initialization_matrix(6, &expected);
  ck_assert_int_eq(s21_mult_number(&a, 3, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_matrix_1) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 5;
  a.matrix[0][1] = 2;
  a.matrix[1][0] = 3;
  a.matrix[1][1] = 1;
  s21_create_matrix(2, 2, &b);
  b.matrix[0][0] = 4;
  b.matrix[0][1] = 6;
  b.matrix[1][0] = 5;
  b.matrix[1][1] = 2;
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = 30;
  expected.matrix[0][1] = 34;
  expected.matrix[1][0] = 17;
  expected.matrix[1][1] = 20;
  s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(!s21_eq_matrix(&result, &expected), OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_matrix_invalid_matrix) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 0, &a);
  s21_create_matrix(2, 2, &b);
  b.matrix[0][0] = 4;
  b.matrix[0][1] = 6;
  b.matrix[1][0] = 5;
  b.matrix[1][1] = 2;
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = 30;
  expected.matrix[0][1] = 34;
  expected.matrix[1][0] = 17;
  expected.matrix[1][1] = 20;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_transpose_invalid_matrix) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 0, &a);
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 3;
  expected.matrix[1][1] = 5;
  ck_assert_int_eq(s21_transpose(&a, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_transpose_1) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 3;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 3;
  expected.matrix[1][1] = 5;
  s21_transpose(&a, &result);
  ck_assert_int_eq(!s21_eq_matrix(&result, &expected), OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_calc_invalid_matrix) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(3, 0, &a);
  // s21_create_matrix(3, 3, &result);
  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;
  ck_assert_int_eq(s21_calc_complements(&a, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_calc_diff_size) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;
  s21_calc_complements(&a, &result);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_calc_1) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  // s21_create_matrix(3, 3, &result);
  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;
  s21_calc_complements(&a, &result);
  ck_assert_int_eq(!s21_eq_matrix(&result, &expected), OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_det_invalid_matrix) {
  matrix_t a = {0};
  double result = 0;
  s21_create_matrix(3, 0, &a);
  ck_assert_int_eq(s21_determinant(&a, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test_det_1) {
  matrix_t a;
  double result = 0;
  double expected = -52;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 3;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 5;
  a.matrix[1][1] = 7;
  a.matrix[1][2] = 6;
  a.matrix[2][0] = 4;
  a.matrix[2][1] = 9;
  a.matrix[2][2] = 1;
  s21_determinant(&a, &result);
  ck_assert_double_eq(result, expected);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(test_inv_invalid_matrix) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 0, &a);
  // a.matrix[0][0] = 1;
  // a.matrix[0][1] = 3;
  // a.matrix[1][0] = 4;
  // a.matrix[1][1] = 2;
  // s21_create_matrix(2, 0, &result);
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = -0.2;
  expected.matrix[0][1] = 0.3;
  expected.matrix[1][0] = 0.4;
  expected.matrix[1][1] = -0.1;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inv_diff_size) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 3, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 3;
  a.matrix[0][2] = 5;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 2;
  a.matrix[1][2] = 6;
  // s21_create_matrix(3, 3, &result);
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = -0;
  expected.matrix[0][1] = 0;
  expected.matrix[1][0] = -0;
  expected.matrix[1][1] = 0;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), CALCULATION_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inv_1) {
  matrix_t a = {0};
  matrix_t result = {0};
  matrix_t expected = {0};
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 3;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 2;
  // s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = -0.2;
  expected.matrix[0][1] = 0.3;
  expected.matrix[1][0] = 0.4;
  expected.matrix[1][1] = -0.1;
  s21_inverse_matrix(&a, &result);
  ck_assert_int_eq(!s21_eq_matrix(&result, &expected), OK);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("S21_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_create_invalid_matrix);
  tcase_add_test(tc_core, test_eq_matrix_1);
  tcase_add_test(tc_core, test_sum_diff_size);
  tcase_add_test(tc_core, test_sum_invalid_matrix);
  tcase_add_test(tc_core, test_sum_1);
  tcase_add_test(tc_core, test_sub_diff_size);
  tcase_add_test(tc_core, test_sub_invalid_matrix);
  tcase_add_test(tc_core, test_sub_1);
  tcase_add_test(tc_core, test_mult_matrix_1);
  tcase_add_test(tc_core, test_mult_matrix_invalid_matrix);
  tcase_add_test(tc_core, test_mult_number_1);
  tcase_add_test(tc_core, test_mult_number_invalid_matrix);
  tcase_add_test(tc_core, test_calc_1);
  tcase_add_test(tc_core, test_calc_diff_size);
  tcase_add_test(tc_core, test_calc_invalid_matrix);
  tcase_add_test(tc_core, test_transpose_1);
  tcase_add_test(tc_core, test_transpose_invalid_matrix);

  tcase_add_test(tc_core, test_det_1);
  tcase_add_test(tc_core, test_det_invalid_matrix);
  tcase_add_test(tc_core, test_inv_1);
  tcase_add_test(tc_core, test_inv_diff_size);
  tcase_add_test(tc_core, test_inv_invalid_matrix);

  suite_add_tcase(suite, tc_core);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_VERBOSE);

  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failures == 0) ? 0 : 1;
}
