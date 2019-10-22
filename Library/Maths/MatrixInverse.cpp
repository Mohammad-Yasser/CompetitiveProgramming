
typedef double Double;
typedef vector<Double> Row;
typedef vector<Row> Matrix;

void printMatrix(const Matrix& mat) {
  int n = mat.size();
  int m = mat[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
}

Matrix getEmptyMatrix(int n, int m) {
  return Matrix(n, Row(m, 0));
}

Matrix inverseOfMatrix(const Matrix& matrix) {
  int n = matrix.size();
  // Create the augmented matrix
  // Add the identity matrix
  // of order at the end of original matrix.
  int m = 2 * n;
  Matrix augmented = getEmptyMatrix(n, m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j < n) {
        augmented[i][j] = matrix[i][j];
      } else {
        if (j == (i + n)) {
          augmented[i][j] = 1;
        }
      }
    }
  }

  // Interchange the row of matrix,
  // interchanging of row will start from the last row
  for (int i = n - 1; i > 0; i--) {
    if (augmented[i - 1][0] < augmented[i][0]) {
      swap(augmented[i], augmented[i - 1]);
    }
  }

  // Replace a row by sum of itself and a
  // constant multiple of another row of the matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j != i) {
        Double temp = augmented[j][i] / augmented[i][i];
        for (int k = 0; k < 2 * n; k++) {
          augmented[j][k] -= augmented[i][k] * temp;
        }
      }
    }
  }

  // Multiply each row by a nonzero integer.
  // Divide row element by the diagonal element
  for (int i = 0; i < n; i++) {
    Double temp = augmented[i][i];
    for (int j = 0; j < 2 * n; j++) {
      augmented[i][j] /= temp;
    }
  }

  Matrix result = getEmptyMatrix(n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      result[i][j] = augmented[i][j + n];
    }
  }

  return result;
}
