#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
  int n;
  double *data;
} Matrix;

#define MAT(m, i, j) ((m)->data[(i) * (m)->n + (j)])

Matrix *matrix_create(int n);
void matrix_free(Matrix *m);
void matrix_fill_random(Matrix *m, unsigned int seed);
void matrix_print(const Matrix *m, int max_rows);

Matrix *matrix_add(const Matrix *A, const Matrix *B);
Matrix *matrix_sub(const Matrix *A, const Matrix *B);
Matrix *matrix_get_quadrant(const Matrix *A, int row, int col);

Matrix *multiply_std(const Matrix *A, const Matrix *B);
Matrix *multiply_strassen(const Matrix *A, const Matrix *B);

#endif
