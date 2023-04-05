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