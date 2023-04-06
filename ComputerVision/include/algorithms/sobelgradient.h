#pragma once
#include "types/matrix.h"

namespace cv
{
  namespace algorithms
  {
    class SobelGradient
    {
    private:
      types::Matrix3D _Gx = types::Matrix3D(-1.0, 0.0, 1.0,
        -2.0, 0.0, 2.0,
        -1.0, 0.0, 1.0);
      types::Matrix3D _GY = types::Matrix3D(1.0, 2.0, 1.0,
        0.0, 0.0, 0.0,
        -1.0, -2.0, -1.0);
      types::Matrix _imgArray;
    public:
      SobelGradient(std::string imgPath);
    public:
      bool Apply();
    };
  }
}