#include <stdio.h>
#include <time.h>
#include "matrix.h"

int main(void) {
  int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256};
  int num_sizes = 8;

  for (int s = 0; s < num_sizes; s++) {
    int n = sizes[s];

    Matrix *A = matrix_create(n);
    Matrix *B = matrix_create(n);
    matrix_fill_random(A, 42);
    matrix_fill_random(B, 123);

    clock_t inicio, fin;

    inicio = clock();
    Matrix *C = multiply_std(A, B);
    fin = clock();
    double tiempo_std = (double)(fin - inicio) / CLOCKS_PER_SEC;

    inicio = clock();
    Matrix *D = multiply_strassen(A, B);
    fin = clock();
    double tiempo_str = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("n=%d | std: %.6f s | strassen: %.6f s\n", n, tiempo_std, tiempo_str);

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(D);
  }

  return 0;
}
