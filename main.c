#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "matrix.h"

#define REPETICIONES 7

int comparar(const void *a, const void *b) {
  double da = *(double *)a;
  double db = *(double *)b;
  return (da > db) - (da < db);
}

double mediana(double *arr, int n) {
  qsort(arr, n, sizeof(double), comparar);
  return arr[n / 2];
}

int main(void) {
  int sizes[] = {2, 4, 8, 16, 32, 48, 64, 80, 96, 112, 128, 192, 256};
  int num_sizes = 13;

  FILE *csv = fopen("resultados.csv", "w");
  fprintf(csv, "n,mediana_std,mediana_strassen\n");

  for (int s = 0; s < num_sizes; s++) {
    int n = sizes[s];

    double tiempos_std[REPETICIONES];
    double tiempos_str[REPETICIONES];

    for (int r = 0; r < REPETICIONES; r++) {
      Matrix *A = matrix_create(n);
      Matrix *B = matrix_create(n);
      matrix_fill_random(A, 42 + r);
      matrix_fill_random(B, 123 + r);

      clock_t inicio, fin;

      inicio = clock();
      Matrix *C = multiply_std(A, B);
      fin = clock();
      tiempos_std[r] = (double)(fin - inicio) / CLOCKS_PER_SEC;

      inicio = clock();
      Matrix *D = multiply_strassen(A, B);
      fin = clock();
      tiempos_str[r] = (double)(fin - inicio) / CLOCKS_PER_SEC;

      matrix_free(A);
      matrix_free(B);
      matrix_free(C);
      matrix_free(D);
    }

    double med_std = mediana(tiempos_std, REPETICIONES);
    double med_str = mediana(tiempos_str, REPETICIONES);

    printf("n=%d | std: %.6f s | strassen: %.6f s\n", n, med_std, med_str);
    fprintf(csv, "%d,%.6f,%.6f\n", n, med_std, med_str);
  }

  fclose(csv);
  printf("Resultados guardados en resultados.csv\n");
  return 0;
}
