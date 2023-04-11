#include <iostream>
#include "algorithms/sobelgradient.h"


int main()
{
  auto gradient = cv::algorithms::SobelGradient("C:\\Users\\t.peruzzi\\Desktop\\test_sobel_img.png", 20, false);
  gradient.Apply();
  gradient.Save("C:\\Users\\t.peruzzi\\Desktop\\testConv.png");

  auto gradient2 = cv::algorithms::SobelGradient("C:\\Users\\t.peruzzi\\Desktop\\test_sobel_img.png", 20, true);
  gradient2.Apply();
  gradient2.Save("C:\\Users\\t.peruzzi\\Desktop\\testConv_smooth.png");
}
