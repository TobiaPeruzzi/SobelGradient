#include "types/rgba.h"


cv::types::RGBA::RGBA(int r, int g, int b, int a)
{
  R = r;
  G = g;
  B = b;
  A = a;
}

double cv::types::RGBA::Dot(RGBA& pt)
{
  return R * pt.R + G * pt.G + B * pt.B + A * pt.A;
}

void cv::types::RGBA::Scale(int val)
{
  R *= val;
  G *= val;
  B *= val;
  //A* val;
}

void cv::types::RGBA::Sum(RGBA& pt)
{
  R += pt.R;
  G += pt.G;
  B += pt.B;
  //A + pt.A;
}
