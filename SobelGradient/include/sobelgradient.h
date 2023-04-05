#pragma once
#include "matrix3d.h"

namespace cv
{
  class SobelGradient
  {
  private:
    Matrix3D _Gx = Matrix3D(-1.0, 0.0, 1.0,
      -2.0, 0.0, 2.0,
      -1.0, 0.0, 1.0);
    Matrix3D _GY = Matrix3D(1.0, 2.0, 1.0,
      0.0, 0.0, 0.0,
      -1.0, -2.0, -1.0);
  public:
    SobelGradient();

  };
}