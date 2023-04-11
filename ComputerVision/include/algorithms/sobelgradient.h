#pragma once
#include "types/matrix.h"

namespace cv
{
  namespace algorithms
  {
    class SobelGradient
    {
    private:
      //the following matrices are not actually the sobel one, but are the sobel one with rows and columns flipped.
      //This is done to speed up the calculation, since in the convolution step the kernels (i.e. Gx and Gy) are flipped
      //both row-wise and column-wise
      types::Matrix3D _Gx = types::Matrix3D(-1.0, 0.0, 1.0,
        -2.0, 0.0, 2.0,
        -1.0, 0.0, 1.0);
      types::Matrix3D _Gy = types::Matrix3D(1.0, 2.0, 1.0,
        0.0, 0.0, 0.0,
        -1.0, -2.0, -1.0);
      types::Matrix3D _smoothing;
      types::Matrix* _imgArray;
      double _threshold;
      int _rows;
      int _cols;
      std::vector<unsigned char> _result;
    public:
      SobelGradient(std::string imgPath, double threshold = 20, bool smoothing = true);
      ~SobelGradient();
    public:
      bool Apply();
      bool Save(std::string savePath);
    private:
      void Smoothing();
      void SobelConvolution(types::Matrix3D* patch, double& xConv, double& yConv);
      void SmoothingConvolution(types::Matrix3D* patch, double& smooth);
    };
  }
}