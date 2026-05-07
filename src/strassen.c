#include <stdlib.h>
#include "matrix.h"

Matrix *multiply_strassen(const Matrix *A, const Matrix *B) {
  int n = A->n;

  if (n == 1) {
    Matrix *C = matrix_create(1);
    MAT(C, 0, 0) = MAT(A, 0, 0) * MAT(B, 0, 0);
    return C;
  }

  int half = n / 2;

  Matrix *a = matrix_get_quadrant(A, 0, 0);
  Matrix *b = matrix_get_quadrant(A, 0, half);
  Matrix *c = matrix_get_quadrant(A, half, 0);
  Matrix *d = matrix_get_quadrant(A, half, half);

  Matrix *e = matrix_get_quadrant(B, 0, 0);
  Matrix *f = matrix_get_quadrant(B, 0, half);
  Matrix *g = matrix_get_quadrant(B, half, 0);
  Matrix *h = matrix_get_quadrant(B, half, half);

  Matrix *f_h   = matrix_sub(f, h);
  Matrix *a_b   = matrix_add(a, b);
  Matrix *c_d   = matrix_add(c, d);
  Matrix *g_e   = matrix_sub(g, e);
  Matrix *a_d   = matrix_add(a, d);
  Matrix *e_h   = matrix_add(e, h);
  Matrix *b_d   = matrix_sub(b, d);
  Matrix *g_h   = matrix_add(g, h);
  Matrix *a_c   = matrix_sub(a, c);
  Matrix *e_f   = matrix_add(e, f);

  Matrix *P1 = multiply_strassen(a, f_h);
  Matrix *P2 = multiply_strassen(a_b, h);
  Matrix *P3 = multiply_strassen(c_d, e);
  Matrix *P4 = multiply_strassen(d, g_e);
  Matrix *P5 = multiply_strassen(a_d, e_h);
  Matrix *P6 = multiply_strassen(b_d, g_h);
  Matrix *P7 = multiply_strassen(a_c, e_f);

  Matrix *P5_P4 = matrix_add(P5, P4);
  Matrix *P5_P4_P2 = matrix_sub(P5_P4, P2);
  Matrix *C11 = matrix_add(P5_P4_P2, P6);

  Matrix *C12 = matrix_add(P1, P2);

  Matrix *C21 = matrix_add(P3, P4);

  Matrix *P5_P1 = matrix_add(P5, P1);
  Matrix *P5_P1_P3 = matrix_sub(P5_P1, P3);
  Matrix *C22 = matrix_sub(P5_P1_P3, P7);

  Matrix *C = matrix_create(n);
  for (int i = 0; i < half; i++) {
    for (int j = 0; j < half; j++) {
      MAT(C, i,        j)        = MAT(C11, i, j);
      MAT(C, i,        j + half) = MAT(C12, i, j);
      MAT(C, i + half, j)        = MAT(C21, i, j);
      MAT(C, i + half, j + half) = MAT(C22, i, j);
    }
  }

  matrix_free(a);  matrix_free(b);  matrix_free(c);  matrix_free(d);
  matrix_free(e);  matrix_free(f);  matrix_free(g);  matrix_free(h);
  matrix_free(f_h); matrix_free(a_b); matrix_free(c_d); matrix_free(g_e);
  matrix_free(a_d); matrix_free(e_h); matrix_free(b_d); matrix_free(g_h);
  matrix_free(a_c); matrix_free(e_f);
  matrix_free(P1); matrix_free(P2); matrix_free(P3); matrix_free(P4);
  matrix_free(P5); matrix_free(P6); matrix_free(P7);
  matrix_free(C11); matrix_free(C12); matrix_free(C21); matrix_free(C22);
  matrix_free(P5_P4); matrix_free(P5_P4_P2);
  matrix_free(P5_P1); matrix_free(P5_P1_P3);

  return C;
}
