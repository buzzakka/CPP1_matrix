#include "s21_matrix_oop.h"

namespace s21_matrix_oop {
//    **************************************************
//    *             Вспомогательные функции            *
//    **************************************************

//    Выделение памяти под матрицу matrix_ и заполнение её нулями
//    Условия для throw: значениея rows и cols меньше или равно 0
double **S21Matrix::MakeMatrix(int rows, int cols) {
  if (rows <= 0) {
    throw std::out_of_range(
        "Некорректные входные данные: значение rows должно быть больше 0.");
  }
  if (cols <= 0) {
    throw std::out_of_range(
        "Некорректные входные данные: значение cols должно быть больше 0.");
  }
  double **matrix = new double *[rows] {};
  for (int row{}; row < rows; row++) {
    matrix[row] = new double[cols]{};
  }
  return matrix;
}

//    Копирование значений из matrix1 в matrix2
void S21Matrix::CopyMatrix(double **matrix1, double **matrix2) const noexcept {
  for (int row{}; row < rows_; row++) {
    for (int col{}; col < cols_; col++) {
      matrix2[row][col] = matrix1[row][col];
    }
  }
}

//    Очистка выделенной под матрицу matrix_ памяти
void S21Matrix::DestroyMatrix() noexcept {
  if (matrix_) {
    for (int row{}; row < rows_; row++) {
      delete[] matrix_[row];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

//    Вычисление минора матрицы matrix_
double S21Matrix::GetMinor(int row, int col) const {
  double minor_value = 0.;
  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
  MakeMatrixForMinor(row, col, minor_matrix.matrix_);
  minor_value = minor_matrix.Determinant();
  return minor_value;
}

//    Создание матрицы для расчёта минора матрицы
//    Условия для throw: матрица matrix_ не является квадратной
void S21Matrix::MakeMatrixForMinor(int row, int col,
                                   double **matrix) const noexcept {
  int new_row = 0;
  int new_col = 0;

  for (int current_row = 0; current_row < rows_; current_row++) {
    if (current_row != row) {
      for (int current_col = 0; current_col < cols_; current_col++) {
        if (current_col != col) {
          matrix[new_row][new_col++] = matrix_[current_row][current_col];
        }
      }
      new_row++;
      new_col = 0;
    }
  }
}
}  // namespace s21_matrix_oop
