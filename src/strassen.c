#include <stdlib.h>
#include "matrix.h"

Matrix *multiply_strassen(const Matrix *A, const Matrix *B) {
  int n = A->n;

  if (n == 1) {
    Matrix *C = matrix_create(1);
    MAT(C, 0, 0) = MAT(A, 0, 0) * MAT(B, 0, 0);
    return C;
  }

  return multiply_std(A, B);
}
