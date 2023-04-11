#include "types/matrix.h"


cv::types::Matrix3D::Matrix3D(double seed) : Matrix(3, 3, seed)
{
  memset(_data, (int)seed, (size_t)(_rows * _cols) * sizeof(double));
}

cv::types::Matrix3D::Matrix3D(double a, double b, double c,
  double d, double e, double f,
  double g, double h, double i) : Matrix(3, 3)
{
  Set(0, 0, a);
  Set(0, 1, b);
  Set(0, 2, c);
  Set(1, 0, d);
  Set(1, 1, e);
  Set(1, 2, f);
  Set(2, 0, g);
  Set(2, 1, h);
  Set(2, 2, i);
}

bool cv::types::Matrix3D::Padding(int& centerRow, int& centerColumn)
{
  if (centerRow == 0 && centerColumn != 0 && centerColumn != _cols - 1)
  {
    int prevCol = centerColumn - 1;
    int nextCol = centerColumn + 1;
    Set(0, 0, Get(0, prevCol));
    Set(0, 1, Get(0, centerColumn));
    Set(0, 2, Get(0, nextCol));
    Set(1, 0, Get(0, prevCol));
    Set(1, 1, Get(0, centerColumn));
    Set(1, 2, Get(0, nextCol));
    Set(2, 0, Get(1, prevCol));
    Set(2, 1, Get(1, centerColumn));
    Set(2, 2, Get(1, nextCol));
    return true;
  }
  if (centerRow == 0 && centerColumn == 0)
  {
    Set(0, 0, Get(0, 0));
    Set(0, 1, Get(0, 0));
    Set(0, 2, Get(0, 1));
    Set(1, 0, Get(0, 0));
    Set(1, 1, Get(0, 0));
    Set(1, 2, Get(0, 1));
    Set(2, 0, Get(1, 0));
    Set(2, 1, Get(1, 0));
    Set(2, 2, Get(1, 1));
    return true;
  }
  if (centerRow == 0 && centerColumn == _cols - 1)
  {
    int prevCol = centerColumn - 1;
    Set(0, 0, Get(0, prevCol));
    Set(0, 1, Get(0, centerColumn));
    Set(0, 2, Get(0, centerColumn));
    Set(1, 0, Get(0, prevCol));
    Set(1, 1, Get(0, centerColumn));
    Set(1, 2, Get(0, centerColumn));
    Set(2, 0, Get(1, prevCol));
    Set(2, 1, Get(1, centerColumn));
    Set(2, 2, Get(1, centerColumn));
    return true;
  }
  if (centerColumn == 0 && centerRow != 0 && centerRow != _rows - 1)
  {
    int prevRow = centerRow - 1;
    int nextRow = centerRow + 1;
    Set(0, 0, Get(prevRow, 0));
    Set(0, 1, Get(prevRow, 0));
    Set(0, 2, Get(prevRow, 1));
    Set(0, 0, Get(centerRow, 0));
    Set(0, 1, Get(centerRow, 0));
    Set(0, 2, Get(centerRow, 1));
    Set(0, 0, Get(nextRow, 0));
    Set(0, 1, Get(nextRow, 0));
    Set(0, 2, Get(nextRow, 1));
    return true;
  }
  if (centerColumn == 0 && centerRow == _rows - 1)
  {
    int prevRow = centerRow - 1;
    Set(0, 0, Get(prevRow, 0));
    Set(0, 1, Get(prevRow, 0));
    Set(0, 2, Get(prevRow, 1));
    Set(0, 0, Get(centerRow, 0));
    Set(0, 1, Get(centerRow, 0));
    Set(0, 2, Get(centerRow, 1));
    Set(0, 0, Get(centerRow, 0));
    Set(0, 1, Get(centerRow, 0));
    Set(0, 2, Get(centerRow, 1));
    return true;
  }
  if (centerRow == _rows - 1 && centerColumn != 0 && centerColumn != _cols - 1)
  {
    int prevRow = centerRow - 1;
    int prevCol = centerColumn - 1;
    int nextCol = centerColumn + 1;
    Set(0, 0, Get(prevRow, prevCol));
    Set(0, 1, Get(prevRow, centerColumn));
    Set(0, 2, Get(prevRow, nextCol));
    Set(0, 0, Get(centerRow, prevCol));
    Set(0, 1, Get(centerRow, centerColumn));
    Set(0, 2, Get(centerRow, nextCol));
    Set(0, 0, Get(centerRow, prevCol));
    Set(0, 1, Get(centerRow, centerColumn));
    Set(0, 2, Get(centerRow, nextCol));
    return true;
  }
  if (centerRow == _rows - 1 && centerColumn == _cols - 1)
  {
    int prevRow = centerRow - 1;
    int prevCol = centerColumn - 1;
    Set(0, 0, Get(prevRow, prevCol));
    Set(0, 1, Get(prevRow, centerColumn));
    Set(0, 2, Get(prevRow, centerColumn));
    Set(0, 0, Get(centerRow, prevCol));
    Set(0, 1, Get(centerRow, centerColumn));
    Set(0, 2, Get(centerRow, centerColumn));
    Set(0, 0, Get(centerRow, prevCol));
    Set(0, 1, Get(centerRow, centerColumn));
    Set(0, 2, Get(centerRow, centerColumn));
    return true;
  }
  return false;
}
