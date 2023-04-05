#include "types/matrix.h"


cv::types::Matrix::Matrix()
{
  Matrix(1, 1);
}

cv::types::Matrix::Matrix(int rows, int columns, double seed)
{
  _rows = rows;
  _cols = columns;
  auto size = (size_t)_rows * _cols;
  _data = new double[size];
  memset(_data, (int)seed, size * sizeof(double));
}

bool cv::types::Matrix::Set(int row, int column, double value)
{
  RangeCheck(row, column);
  _data[row * _cols + column] = value;
  return true;
}

double cv::types::Matrix::Get(int row, int column)
{
  RangeCheck(row, column);
  return _data[row * _cols + column];
}

bool cv::types::Matrix::Resize(int rows, int columns)
{
  auto size = (size_t)rows * columns;
  size_t oldSize = (size_t)(_rows * _cols);
  if (size == oldSize)  return true;
  auto newMatrix = Matrix(rows, columns);
  if (size > oldSize)
  {
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++)
        newMatrix.Set(i, j, Get(i, j));
  }
  else // size < oldSize
  {
    int tmpRows = std::min(rows, _rows);
    int tmpCols = std::min(columns, _cols);
    for (int i = 0; i < tmpRows; i++)
      for (int j = 0; j < tmpCols; j++)
        newMatrix.Set(i, j, Get(i, j));
  }
  _rows = rows;
  _cols = columns;
  _data = newMatrix._data;
}

void cv::types::Matrix::RangeCheck(int& i, int& j)
{
  if (i < 0) i = 0;
  if (j < 0) j = 0;
  if (i >= _rows) i = _rows - 1;
  if (j >= _cols) j = _cols - 1;
}
