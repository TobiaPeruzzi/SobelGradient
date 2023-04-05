#include "matrix.h"


cv::Matrix::Matrix(int width, int height, double seed)
{
  _width = width;
  _height = height;
  auto size = (size_t)width * height;
  _data = new double[size];
  memset(_data, seed, size * sizeof(double));
}

bool cv::Matrix::Set(int i, int j, double value)
{
  _data[i * _height + j] = value;
  return true;
}