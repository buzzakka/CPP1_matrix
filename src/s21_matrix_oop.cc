#include "s21_matrix_oop.h"

namespace s21_matrix_oop {

//    **************************************************
//    *        Конструкторы и деструктор матрицы       *
//    **************************************************

//    Параметризированный конструктор с количеством строк rows и столбцов cols
//    Условия для throw: rows <= 0 или cols <= 0
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = MakeMatrix(rows_, cols_);
}

//    Параметризированный конструктор, инициализирующий квадратную матрицу
S21Matrix::S21Matrix(int rows) : S21Matrix(rows, rows) {}

//    Базовый конструктор, инициализирующий матрицу некоторой заранее
//    заданной размерностью (3x3).
S21Matrix::S21Matrix() : S21Matrix(3) {}

//    Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = MakeMatrix(rows_, cols_);
  for (int row{}; row < rows_; row++) {
    for (int col{}; col < cols_; col++) {
      matrix_[row][col] = other.matrix_[row][col];
    }
  }
}

//    Конструктор переноса
S21Matrix::S21Matrix(S21Matrix &&other) {
  matrix_ = MakeMatrix(other.rows_, other.cols_);
  rows_ = other.rows_;
  cols_ = other.cols_;
  CopyMatrix(other.matrix_, matrix_);
  other.DestroyMatrix();
  other.cols_ = 0;
  other.rows_ = 0;
}

//    Деструктор
S21Matrix::~S21Matrix() {
  DestroyMatrix();
  cols_ = 0;
  rows_ = 0;
}

//    **************************************************
//    *                Геттеры и Сеттеры               *
//    **************************************************

int S21Matrix::getRows() const noexcept { return rows_; }

int S21Matrix::getCols() const noexcept { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows <= 0) {
    throw std::out_of_range(
        "Некорректные входные данные: значение rows должно быть больше 0.");
  }
  if (rows < rows_) {
    while (rows_ != rows) {
      rows_--;
      delete[] matrix_[rows_];
    }
  } else if (rows > rows_) {
    double **temp_matrix = MakeMatrix(rows, cols_);
    CopyMatrix(matrix_, temp_matrix);
    DestroyMatrix();
    rows_ = rows;
    matrix_ = temp_matrix;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols <= 0) {
    throw std::out_of_range(
        "Некорректные входные данные: значение cols должно быть больше 0.");
  }
  double **temp_matrix = MakeMatrix(rows_, cols);
  if (cols < cols_) {
    for (int row = 0; row < rows_; row++) {
      for (int col = 0; col < cols; col++) {
        temp_matrix[row][col] = matrix_[row][col];
      }
    }
  } else if (cols > cols_) {
    CopyMatrix(matrix_, temp_matrix);
  }
  DestroyMatrix();
  cols_ = cols;
  matrix_ = temp_matrix;
}

//    Заполнение матрицы matrix_ значениями одномерной матрицы
//    matrix[] с размером size
void S21Matrix::setMatrix(double matrix[], size_t size) {
  size_t count = 0;
  for (int row = 0; row < rows_ && count != size; row++) {
    for (int col = 0; col < cols_ && count != size; col++) {
      matrix_[row][col] = matrix[count++];
    }
  }
}

//    **************************************************
//    *          Основные функции с матрицами          *
//    **************************************************

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool result = (rows_ == other.rows_ && cols_ == other.cols_);
  for (int row{}; row < rows_ && result == true; row++) {
    for (int col{}; col < cols_ && result == true; col++) {
      if (fabs(other.matrix_[row][col] - matrix_[row][col]) > 1e-07)
        result = false;
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::out_of_range(
        "Некорректные входные данные: различная размерность матриц.");
  }
  for (int row{}; row < rows_; row++) {
    for (int col{}; col < cols_; col++) {
      matrix_[row][col] += other.matrix_[row][col];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::out_of_range(
        "Некорректные входные данные: различная размерность матриц.");
  }
  for (int row{}; row < rows_; row++) {
    for (int col{}; col < cols_; col++) {
      matrix_[row][col] -= other.matrix_[row][col];
    }
  }
}

void S21Matrix::MulNumber(double num) noexcept {
  for (int row{}; row < rows_; row++) {
    for (int col{}; col < cols_; col++) {
      matrix_[row][col] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Некорректные входные данные: число столбцов первой матрицы не равно "
        "числу строк второй матрицы.");
  }
  double **result_matrix = MakeMatrix(rows_, other.cols_);
  for (int row{}; row < rows_; row++) {
    for (int col{}; col < other.cols_; col++) {
      for (int k{}; k < cols_; k++)
        result_matrix[row][col] += matrix_[row][k] * other.matrix_[k][col];
    }
  }
  DestroyMatrix();
  matrix_ = result_matrix;
  rows_ = other.rows_;
  cols_ = other.cols_;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix result_matrix(cols_, rows_);
  for (int row{}; row < result_matrix.rows_; row++)
    for (int col{}; col < result_matrix.cols_; col++)
      result_matrix.matrix_[row][col] = matrix_[col][row];
  return result_matrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (cols_ != rows_) {
    throw std::out_of_range(
        "Некорректные входные данные: матрица не является квадратной.");
  }
  S21Matrix result_matrix(rows_, cols_);
  for (int row{}; row < rows_; row++)
    for (int col{}; col < cols_; col++) {
      result_matrix.matrix_[row][col] = GetMinor(row, col) * pow(-1, row + col);
    }
  return result_matrix;
}

double S21Matrix::Determinant() const {
  if (cols_ != rows_) {
    throw std::out_of_range(
        "Некорректные входные данные: матрица не является квадратной.");
  }
  double result{};
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix algebr_matrix = CalcComplements();
    for (int col = 0; col < cols_; col++)
      result += matrix_[0][col] * algebr_matrix.matrix_[0][col];
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = Determinant();
  if (fabs(determinant) <= 1e-6) {
    throw std::out_of_range(
        "Некорректные входные данные: определитель матрицы равен 0.");
  }

  S21Matrix alg_compl = CalcComplements();
  S21Matrix alg_compl_tran = alg_compl.Transpose();
  S21Matrix inverse_matrix(rows_, cols_);
  for (int row{}; row < rows_; row++)
    for (int col{}; col < cols_; col++)
      inverse_matrix.matrix_[row][col] =
          alg_compl_tran.matrix_[row][col] / determinant;

  return inverse_matrix;
}

//**************************************************
//*              Перегрузка операторов             *
//**************************************************

//    result = S21Matrix + S21Matrix
//    Условия для throw: различная размерность матриц matrix_ и matirx
S21Matrix S21Matrix::operator+(const S21Matrix &matrix) {
  S21Matrix result(rows_, cols_);
  result.CopyMatrix(matrix_, result.matrix_);
  result.SumMatrix(matrix);
  return result;
}

//    result = S21Matrix - S21Matrix
//    Условия для throw: различная размерность матриц matrix_ и matirx
S21Matrix S21Matrix::operator-(const S21Matrix &matrix) {
  S21Matrix result(rows_, cols_);
  result.CopyMatrix(matrix_, result.matrix_);
  result.SubMatrix(matrix);
  return result;
}

//    result = S21Matrix * num
S21Matrix S21Matrix::operator*(double num) noexcept {
  S21Matrix result(rows_, cols_);
  result.CopyMatrix(matrix_, result.matrix_);
  result.MulNumber(num);
  return result;
}

//    result = num * S21Matrix
S21Matrix operator*(double num, const S21Matrix &matrix) noexcept {
  S21Matrix result(matrix.rows_, matrix.cols_);
  result.CopyMatrix(matrix.matrix_, result.matrix_);
  result.MulNumber(num);
  return result;
}

//    result =  S21Matrix * S21Matrix
//    Условия для throw: число столбцов matrix_ не равно числу строк matrix.
S21Matrix S21Matrix::operator*(const S21Matrix &matrix) {
  S21Matrix result(rows_, cols_);
  result.CopyMatrix(matrix_, result.matrix_);
  result.MulMatrix(matrix);
  return result;
}

//    S21Matrix == S21Matrix
bool S21Matrix::operator==(const S21Matrix &matrix) const noexcept {
  return EqMatrix(matrix);
}

//    S21Matrix += S21Matrix
//    Условия для throw: различная размерность матриц matrix_ и matrix
S21Matrix S21Matrix::operator+=(const S21Matrix &matrix) {
  SumMatrix(matrix);
  return *this;
}

//    S21Matrix -= S21Matrix
//    Условия для throw: различная размерность матриц matrix_ и matrix
S21Matrix S21Matrix::operator-=(const S21Matrix &matrix) {
  SubMatrix(matrix);
  return *this;
}

//    S21Matrix *= S21Matrix
//    Условия для throw: число столбцов matrix_ не равно числу строк matrix.
S21Matrix S21Matrix::operator*=(const S21Matrix &matrix) {
  MulMatrix(matrix);
  return *this;
}

//    S21Matrix *= num
S21Matrix S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

//    S21Matrix_1 = S21Matrix_2
//    Оператор присваивание копированием
S21Matrix &S21Matrix::operator=(const S21Matrix &matrix) {
  setRows(matrix.rows_);
  setCols(matrix.cols_);
  for (int row{}; row < rows_; row++) {
    for (int col{}; col < cols_; col++) {
      matrix_[row][col] = matrix.matrix_[row][col];
    }
  }
  return *this;
}

//    S21Matrix_1 = S21Matrix_2
//    Оператор присваивание перемещением
S21Matrix S21Matrix::operator=(S21Matrix &&matrix) {
  setRows(matrix.rows_);
  setCols(matrix.cols_);
  CopyMatrix(matrix.matrix_, matrix_);
  matrix.DestroyMatrix();
  matrix.rows_ = 0;
  matrix.cols_ = 0;
  return *this;
}

//    double num = S21matrix(row, col)
//    Условия для throw: row и col не входят в границы [0, rows_) и [0, cols_)
double &S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range(
        "Некорректные входные данные: row и col должны быть больше 0 и меньше "
        "rows_ и cols_ .");
  }
  return matrix_[row][col];
}

}  // namespace s21_matrix_oop
