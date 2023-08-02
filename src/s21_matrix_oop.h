#ifndef CPP_S21_MATRIXPLUS_2_SRC_S21_MATRIX_OOP_H
#define CPP_S21_MATRIXPLUS_2_SRC_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

namespace s21_matrix_oop {
// Класс для работы с матрицами,
class S21Matrix {
 public:
  //   Конструкторы и деструктор
  S21Matrix();
  explicit S21Matrix(int rows);
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  //   Геттеры и Сеттеры
  int getRows() const noexcept;
  int getCols() const noexcept;
  void setRows(int rows);
  void setCols(int cols);
  void setMatrix(double matrix[], size_t size);

  //   Методы для задания
  bool EqMatrix(const S21Matrix &other) const noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  //   Перегрузка операторов
  S21Matrix operator+(const S21Matrix &matrix);
  S21Matrix operator-(const S21Matrix &matrix);
  S21Matrix operator*(double num) noexcept;
  friend S21Matrix operator*(double num, const S21Matrix &matrix) noexcept;
  S21Matrix operator*(const S21Matrix &matrix);
  bool operator==(const S21Matrix &matrix) const noexcept;
  S21Matrix operator+=(const S21Matrix &matrix);
  S21Matrix operator-=(const S21Matrix &matrix);
  S21Matrix operator*=(const S21Matrix &matrix);
  S21Matrix operator*=(double num);
  S21Matrix &operator=(const S21Matrix &matrix);
  S21Matrix operator=(S21Matrix &&matrix);
  double &operator()(int row, int col) const;

 protected:
  //   Вспомогательные методы
  double **MakeMatrix(int rows, int cols);
  void CopyMatrix(double **matrix1, double **matrix2) const noexcept;
  void DestroyMatrix() noexcept;
  double GetMinor(int row, int col) const;
  void MakeMatrixForMinor(int row, int col, double **matrix) const noexcept;

 private:
  int rows_, cols_;
  double **matrix_;
};

S21Matrix operator*(double num, const S21Matrix &matrix) noexcept;
}  // namespace s21_matrix_oop

#endif  // CPP_S21_MATRIXPLUS_2_SRC_S21_MATRIX_OOP_H
