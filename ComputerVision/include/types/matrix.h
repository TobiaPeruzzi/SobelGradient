#pragma once
#include <iostream>
#include <vector>
#include "rgba.h"

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
      Matrix(std::vector<unsigned char> data, int rows, int columns);
    public:
      virtual bool Set(int row, int column, double value);
      virtual double Get(int row, int column);
      virtual bool Resize(int rows, int columns);
    public:
      int RowN();
      int ColumnsN();
      std::vector<unsigned char> GetImgOutput();
    protected:
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

    class RGBAMatrix
    {
    private:
      RGBA* _data;
      int _rows;
      int _cols;
    public:
      RGBAMatrix(int rows, int columns);
      RGBAMatrix(std::vector<unsigned char> data, int rows, int columns);
    public:
      bool Set(int row, int column, RGBA value);
      RGBA Get(int row, int column);
      bool Resize(int rows, int columns);
      std::vector<unsigned char> GetImgOutput();
    private:
      void RangeCheck(int& i, int& j);
    };
  }
}