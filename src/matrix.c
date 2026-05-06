#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix *matrix_create(int n) {
  Matrix *m = malloc(sizeof(Matrix));
  if (!m) return NULL;

  m->n = n;
  m->data = malloc(n * n * sizeof(double));
  if (!m->data) {
    free(m);
    return NULL;
  }

  return m;
}

void matrix_free(Matrix *m) {
  if (!m) return;
  free(m->data);
  free(m);
}

void matrix_fill_random(Matrix *m, unsigned int seed) {
  srand(seed);
  for (int i = 0; i < m->n; i++) {
    for (int j = 0; j < m->n; j++) {
      MAT(m, i, j) = (double)rand() / RAND_MAX;
    }
  }
}

void matrix_print(const Matrix *m, int max_rows) {
  int num_rows = (max_rows < m->n) ? max_rows : m->n;
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < m->n; j++) {
      printf("%6.2f ", MAT(m, i, j));
    }
    printf("\n");
  }
}
