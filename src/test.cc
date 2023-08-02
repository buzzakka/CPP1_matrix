#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

using ::s21_matrix_oop::S21Matrix;

//    **************************************************
//    *          Основные функции с матрицами          *
//    **************************************************

//    EqMatrix
TEST(Basic, EqMatrix1) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2;
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Basic, EqMatrix2) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2;
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

//   SumMatrix
TEST(Basic, SumMatrix1) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2;
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  matrix1.SumMatrix(matrix2);
  for (int i = 0, count = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), matrixValues[count++] * 2);
    }
  }
}

TEST(Basic, SumMatrix2) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(matrix1.SumMatrix(matrix2), std::out_of_range);
}

//   SubMatrix
TEST(Basic, SubMatrix1) {
  S21Matrix matrix1;
  double matrixValues1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues1, std::size(matrixValues1));
  S21Matrix matrix2(3, 3);
  double matrixValues2[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
  matrix2.setMatrix(matrixValues2, std::size(matrixValues2));
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  matrix1.SubMatrix(matrix2);
  for (int i = 0, count = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), matrixValues1[count++] * 2);
    }
  }
}

TEST(Basic, SubMatrix2) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(matrix1.SubMatrix(matrix2), std::out_of_range);
}

//   MulNumber
TEST(Basic, MulNumber) {
  S21Matrix matrix(2);
  double matrixValues[] = {1, 2, 3, 4};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 2);
  matrix.MulNumber(-12.2);
  for (int i = 0, count = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix(i, j), matrixValues[count++] * -12.2);
    }
  }
}

//   MulMatrix
TEST(Basic, MulMatrix1) {
  S21Matrix matrix1(2);
  double matrixValues[] = {1, 2, 3, 4};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2(2);
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 2);
  ASSERT_EQ(matrix2.getRows(), 2);
  ASSERT_EQ(matrix2.getCols(), 2);
  matrix1.MulMatrix(matrix2);
  ASSERT_DOUBLE_EQ(matrix1(0, 0), 7);
  ASSERT_DOUBLE_EQ(matrix1(0, 1), 10);
  ASSERT_DOUBLE_EQ(matrix1(1, 0), 15);
  ASSERT_DOUBLE_EQ(matrix1(1, 1), 22);
}

TEST(Basic, MulMatrix2) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::out_of_range);
}

//    Transpose
TEST(Basic, Transpose) {
  S21Matrix matrix(2, 3);
  double matrixValues[] = {1, 2, 3, 4, 5, 6};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
  S21Matrix result = matrix.Transpose();
  ASSERT_DOUBLE_EQ(result(0, 0), 1);
  ASSERT_DOUBLE_EQ(result(0, 1), 4);
  ASSERT_DOUBLE_EQ(result(1, 0), 2);
  ASSERT_DOUBLE_EQ(result(1, 1), 5);
  ASSERT_DOUBLE_EQ(result(2, 0), 3);
  ASSERT_DOUBLE_EQ(result(2, 1), 6);
}

//   CalcComplements
TEST(Basic, CalcComplements1) {
  S21Matrix matrix(3);
  double matrixValues[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 3);
  ASSERT_EQ(matrix.getCols(), 3);
  S21Matrix result = matrix.CalcComplements();
  ASSERT_DOUBLE_EQ(result(0, 0), 0);
  ASSERT_DOUBLE_EQ(result(0, 1), 10);
  ASSERT_DOUBLE_EQ(result(0, 2), -20);
  ASSERT_DOUBLE_EQ(result(1, 0), 4);
  ASSERT_DOUBLE_EQ(result(1, 1), -14);
  ASSERT_DOUBLE_EQ(result(1, 2), 8);
  ASSERT_DOUBLE_EQ(result(2, 0), -8);
  ASSERT_DOUBLE_EQ(result(2, 1), -2);
  ASSERT_DOUBLE_EQ(result(2, 2), 4);
}

TEST(Basic, CalcComplements2) {
  S21Matrix matrix(2, 3);
  double matrixValues[] = {1, 2, 3, 4, 5, 6};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
  ASSERT_THROW(S21Matrix result = matrix.CalcComplements(), std::out_of_range);
}

//   Determinant
TEST(Basic, Determinant1) {
  S21Matrix matrix(3);
  double matrixValues[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 3);
  ASSERT_EQ(matrix.getCols(), 3);
  double result = matrix.Determinant();
  ASSERT_DOUBLE_EQ(result, -40);
}

TEST(Basic, Determinant2) {
  S21Matrix matrix(2, 3);
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
  ASSERT_THROW(double result = matrix.Determinant(), std::out_of_range);
}

//   InverseMatrix
TEST(Basic, InverseMatrix1) {
  S21Matrix matrix(3);
  double matrixValues[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 3);
  ASSERT_EQ(matrix.getCols(), 3);
  S21Matrix result = matrix.InverseMatrix();
  ASSERT_DOUBLE_EQ(result(0, 0), 0);
  ASSERT_DOUBLE_EQ(result(0, 1), -0.1);
  ASSERT_DOUBLE_EQ(result(0, 2), 0.2);
  ASSERT_DOUBLE_EQ(result(1, 0), -0.25);
  ASSERT_DOUBLE_EQ(result(1, 1), 0.35);
  ASSERT_DOUBLE_EQ(result(1, 2), 0.05);
  ASSERT_DOUBLE_EQ(result(2, 0), 0.5);
  ASSERT_DOUBLE_EQ(result(2, 1), -0.2);
  ASSERT_DOUBLE_EQ(result(2, 2), -0.1);
}

TEST(Basic, InverseMatrix2) {
  S21Matrix matrix(2, 3);
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
  ASSERT_THROW(S21Matrix result = matrix.InverseMatrix(), std::out_of_range);
}

TEST(Basic, InverseMatrix3) {
  S21Matrix matrix(3);
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 3);
  ASSERT_EQ(matrix.getCols(), 3);
  ASSERT_THROW(S21Matrix result = matrix.InverseMatrix(), std::out_of_range);
}

//    **************************************************
//    *              Перегрузка операторов             *
//    **************************************************

//    +
TEST(Overload, Plus1) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2;
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  S21Matrix result = matrix1 + matrix2;
  ASSERT_EQ(result.getRows(), 3);
  ASSERT_EQ(result.getCols(), 3);
  for (int i = 0, count = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      ASSERT_DOUBLE_EQ(result(i, j), matrixValues[count++] * 2);
    }
  }
}

TEST(Overload, Plus2) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(S21Matrix result = matrix1 + matrix2, std::out_of_range);
}

//   -
TEST(Overload, Minus1) {
  S21Matrix matrix1;
  double matrixValues1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues1, std::size(matrixValues1));
  S21Matrix matrix2(3, 3);
  double matrixValues2[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
  matrix2.setMatrix(matrixValues2, std::size(matrixValues2));
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  S21Matrix result = matrix1 - matrix2;
  ASSERT_EQ(result.getRows(), 3);
  ASSERT_EQ(result.getCols(), 3);
  for (int i = 0, count = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      ASSERT_DOUBLE_EQ(result(i, j), matrixValues1[count++] * 2);
    }
  }
}

TEST(Overload, Minus2) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(S21Matrix result = matrix1 - matrix2, std::out_of_range);
}

//   *
TEST(Overload, Mul1) {
  S21Matrix matrix(2);
  double matrixValues[] = {1, 2, 3, 4};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 2);
  S21Matrix result = matrix * -12.2;
  ASSERT_EQ(result.getRows(), 2);
  ASSERT_EQ(result.getCols(), 2);
  for (int i = 0, count = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      ASSERT_DOUBLE_EQ(result(i, j), matrixValues[count++] * -12.2);
    }
  }
}

TEST(Overload, Mul2) {
  S21Matrix matrix(2);
  double matrixValues[] = {1, 2, 3, 4};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 2);
  S21Matrix result = -12.2 * matrix;
  ASSERT_EQ(result.getRows(), 2);
  ASSERT_EQ(result.getCols(), 2);
  for (int i = 0, count = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      ASSERT_DOUBLE_EQ(result(i, j), matrixValues[count++] * -12.2);
    }
  }
}

TEST(Overload, Mul3) {
  S21Matrix matrix1(2);
  double matrixValues[] = {1, 2, 3, 4};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2(2);
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 2);
  ASSERT_EQ(matrix2.getRows(), 2);
  ASSERT_EQ(matrix2.getCols(), 2);
  S21Matrix result = matrix1 * matrix2;
  ASSERT_EQ(result.getRows(), 2);
  ASSERT_EQ(result.getCols(), 2);
  ASSERT_DOUBLE_EQ(result(0, 0), 7);
  ASSERT_DOUBLE_EQ(result(0, 1), 10);
  ASSERT_DOUBLE_EQ(result(1, 0), 15);
  ASSERT_DOUBLE_EQ(result(1, 1), 22);
}

TEST(Overload, Mul4) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(S21Matrix result = matrix1 * matrix2, std::out_of_range);
}

//   ==
TEST(Overload, IsEq1) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2;
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(Overload, IsEq2) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2;
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_FALSE(matrix1 == matrix2);
}

//   =
TEST(Overload, Assignment) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix result = matrix1;
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(result.getRows(), 3);
  ASSERT_EQ(result.getCols(), 3);
  for (int i = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), result(i, j));
    }
  }
}

//   +=
TEST(Overload, PlusAssignment1) {
  S21Matrix matrix1;
  double matrixValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2;
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  matrix1 += matrix2;
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  for (int i = 0, count = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), matrixValues[count++] * 2);
    }
  }
}

TEST(Overload, PlusAssignment2) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(matrix1 += matrix2, std::out_of_range);
}

//   -=
TEST(Overload, MinusAssignment1) {
  S21Matrix matrix1;
  double matrixValues1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  matrix1.setMatrix(matrixValues1, std::size(matrixValues1));
  S21Matrix matrix2(3, 3);
  double matrixValues2[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
  matrix2.setMatrix(matrixValues2, std::size(matrixValues2));
  matrix1 -= matrix2;
  ASSERT_EQ(matrix1.getRows(), 3);
  ASSERT_EQ(matrix1.getCols(), 3);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  for (int i = 0, count = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), matrixValues1[count++] * 2);
    }
  }
}

TEST(Overload, MinusAssignment2) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(matrix1 -= matrix2, std::out_of_range);
}

//   *=
TEST(Overload, MulAssignment1) {
  S21Matrix matrix(2);
  double matrixValues[] = {1, 2, 3, 4};
  matrix.setMatrix(matrixValues, std::size(matrixValues));
  matrix *= -12.2;
  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 2);
  for (int i = 0, count = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix(i, j), matrixValues[count++] * -12.2);
    }
  }
}

TEST(Overload, MulAssignment2) {
  S21Matrix matrix1(2);
  double matrixValues[] = {1, 2, 3, 4};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2(2);
  matrix2.setMatrix(matrixValues, std::size(matrixValues));
  ASSERT_EQ(matrix2.getRows(), 2);
  ASSERT_EQ(matrix2.getCols(), 2);
  matrix1 *= matrix2;
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 2);
  ASSERT_DOUBLE_EQ(matrix1(0, 0), 7);
  ASSERT_DOUBLE_EQ(matrix1(0, 1), 10);
  ASSERT_DOUBLE_EQ(matrix1(1, 0), 15);
  ASSERT_DOUBLE_EQ(matrix1(1, 1), 22);
}

TEST(Overload, MulAssignment4) {
  S21Matrix matrix1(2, 1);
  S21Matrix matrix2(3, 3);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 3);
  ASSERT_EQ(matrix2.getCols(), 3);
  ASSERT_THROW(matrix1 *= matrix2, std::out_of_range);
}

//    **************************************************
//    *        Конструкторы и деструктор матрицы       *
//    **************************************************

TEST(Konstructor, Copy) {
  S21Matrix matrix1(2, 1);
  double matrixValues[] = {1, 2, 3, 4};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2(matrix1);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 1);
  ASSERT_EQ(matrix2.getRows(), 2);
  ASSERT_EQ(matrix2.getCols(), 1);

  for (int i = 0, count = 0; i < matrix2.getRows(); i++) {
    for (int j = 0; j < matrix2.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix2(i, j), matrix1(i, j));
    }
  }
}

TEST(Konstructor, Move) {
  S21Matrix matrix1(2, 1);
  double matrixValues[] = {1, 2, 3, 4};
  matrix1.setMatrix(matrixValues, std::size(matrixValues));
  S21Matrix matrix2(std::move(matrix1));
  ASSERT_EQ(matrix1.getRows(), 0);
  ASSERT_EQ(matrix1.getCols(), 0);
  ASSERT_EQ(matrix2.getRows(), 2);
  ASSERT_EQ(matrix2.getCols(), 1);

  for (int i = 0, count = 0; i < matrix2.getRows(); i++) {
    for (int j = 0; j < matrix2.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix2(i, j), matrixValues[count++]);
    }
  }
}

//    **************************************************
//    *                Геттеры и Сеттеры               *
//    **************************************************

TEST(AccessorMutators, mutator1) {
  S21Matrix matrix1(5);
  ASSERT_EQ(matrix1.getRows(), 5);
  ASSERT_EQ(matrix1.getCols(), 5);
  matrix1.setCols(2);
  matrix1.setRows(2);
  ASSERT_EQ(matrix1.getRows(), 2);
  ASSERT_EQ(matrix1.getCols(), 2);
  for (int i = 0, count = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), 0);
    }
  }
}

TEST(AccessorMutators, mutator2) {
  S21Matrix matrix1(5);
  ASSERT_EQ(matrix1.getRows(), 5);
  ASSERT_EQ(matrix1.getCols(), 5);
  matrix1.setRows(9);
  matrix1.setCols(8);
  ASSERT_EQ(matrix1.getRows(), 9);
  ASSERT_EQ(matrix1.getCols(), 8);
  for (int i = 0, count = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), 0);
    }
  }
}

TEST(AccessorMutators, mutator3) {
  S21Matrix matrix1(5);
  ASSERT_THROW(matrix1.setRows(-4), std::out_of_range);
}

TEST(AccessorMutators, mutator4) {
  S21Matrix matrix1(5);
  ASSERT_THROW(matrix1.setCols(-4), std::out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
