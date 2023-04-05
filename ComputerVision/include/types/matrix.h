#pragma once
#include <iostream>

namespace cv
{
  namespace types
  {
    class Matrix
    {
    private:
      double* _data;
      int _rows;
      int _cols;
    public:
      Matrix();
      Matrix(int rows, int columns, double seed = 0);
    public:
      bool Set(int row, int column, double value);
      double Get(int row, int column);
      bool Resize(int rows, int columns);
    private:
      void RangeCheck(int& i, int& j);
    };

    class Matrix3D : public Matrix
    {
    private:
      double _data[9];
      int _rows = 3;
      int _cols = 3;
    public:
      Matrix3D(double seed = 0);
      Matrix3D(double a, double b, double c,
        double d, double e, double f,
        double g, double h, double i);
    };
  }
}