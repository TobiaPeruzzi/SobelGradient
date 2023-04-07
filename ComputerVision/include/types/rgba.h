#pragma once
#include <iostream>
#include <vector>

namespace cv
{
  namespace types
  {
    class RGBA
    {
    public:
      int R;
      int G;
      int B;
      int A;
    public:
      RGBA(int r = 0, int g = 0, int b = 0, int a = 255);
    public:
      double Dot(RGBA& pt);
      void Scale(int val);
      void Sum(RGBA& pt);
    };
  }
}