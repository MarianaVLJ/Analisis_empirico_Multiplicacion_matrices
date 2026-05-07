#include <stdio.h>
#include "matrix.h"

int main(void) {
  int n = 4;

  Matrix *A = matrix_create(n);
  Matrix *B = matrix_create(n);

  matrix_fill_random(A, 42);
  matrix_fill_random(B, 123);

  Matrix *C = multiply_std(A, B);

  printf("Matriz A (%dx%d):\n", n, n);
  matrix_print(A, n);

  printf("Matriz B (%dx%d):\n", n, n);
  matrix_print(B, n);

  printf("Resultado C = A x B:\n");
  matrix_print(C, n);

  Matrix *D = multiply_strassen(A, B);
  printf("Resultado D = A x B (Strassen):\n");
  matrix_print(D, n);
  matrix_free(D);

  matrix_free(A);
  matrix_free(B);
  matrix_free(C);

  return 0;
}
