#pragma once
#include <iostream>
#include <vector>
#include "rgba.h"

namespace cv
{
  namespace types
  {
    //forward declaration necessary
    class Matrix3D;
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
      void Scale(double s);
    public:
      int RowsN();
      int ColumnsN();
      std::vector<unsigned char> GetImgOutput();
      Matrix3D* Extract3x3Patch(int centerRow, int centerColumn, bool padding = false);
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
    public:
      bool Padding(int& centerRow, int& centerColumn);
    };

    class RGBAMatrix
    {
    private:
      RGBA* _data;
      int _rows;
      int _cols;
    public:
      RGBAMatrix();
      RGBAMatrix(int rows, int columns);
      RGBAMatrix(std::vector<unsigned char> data, int rows, int columns);
    public:
      bool Set(int row, int column, RGBA value);
      RGBA Get(int row, int column);
      bool Resize(int rows, int columns);
      std::vector<unsigned char> GetImgOutput();
      int RowsN();
      int ColumnsN();
      RGBAMatrix* Extract3x3Patch(int centerRow, int centerColumn, bool padding = false);
      Matrix* ConvertGrayscale();
    private:
      void RangeCheck(int& i, int& j);
      bool Padding(int& centerRow, int& centerColumn, RGBAMatrix* data);
    };
  }
}