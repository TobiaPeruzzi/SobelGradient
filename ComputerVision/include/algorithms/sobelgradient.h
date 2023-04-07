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
      types::Matrix3D _GY = types::Matrix3D(1.0, 2.0, 1.0,
        0.0, 0.0, 0.0,
        -1.0, -2.0, -1.0);
      types::RGBAMatrix _imgArray;
    public:
      SobelGradient(std::string imgPath);
    public:
      bool Apply();
    private:
      void Convolution(types::RGBAMatrix* patch, types::RGBA& xConv, types::RGBA& yConv);
    };
  }
}