#pragma once
#include <iostream>

namespace cv
{
  class Matrix
  {
  private:
    double* _data;
    int _width;
    int _height;
  public:
    Matrix(int width, int height, double seed = 0);
  public:
    bool Set(int i, int j, double value);
    double Get(int i, int j);
  };

  class Matrix3D
  {
  private:
    double _data[9];
    int _width = 3;
    int _height = 3;
  public:
    Matrix3D(double seed = 0);
    Matrix3D(double a, double b, double c,
      double d, double e, double f,
      double g, double h, double i);
  public:
    bool Set(int i, int j, double value);
    double Get(int i, int j);
  };
}