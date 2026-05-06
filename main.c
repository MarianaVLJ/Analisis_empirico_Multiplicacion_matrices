#include <stdio.h>
#include "matrix.h"

int main(void) {
  int n = 4;

  Matrix *A = matrix_create(n);
  matrix_fill_random(A, 42);

  printf("Matriz A (%dx%d):\n", n, n);
  matrix_print(A, n);

  matrix_free(A);
  return 0;
}
