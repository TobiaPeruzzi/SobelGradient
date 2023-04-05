#include "matrix.h"


cv::Matrix3D::Matrix3D(double seed)
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) Set(i, j, 0);
}

cv::Matrix3D::Matrix3D(double a, double b, double c,
  double d, double e, double f,
  double g, double h, double i)
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

bool cv::Matrix3D::Set(int i, int j, double value)
{
  if (i < 0) i = 0;
  if (j < 0) j = 0;
  if (i > _height) i = _height;
  if (j > _width) i = _width;
  _data[i * _height + j] = value;
  return true;
}

double cv::Matrix3D::Get(int i, int j)
{
  return _data[i * _height + j];
}