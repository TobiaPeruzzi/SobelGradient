#include <iostream>
#include "algorithms/sobelgradient.h"


int main()
{
  auto gradient = cv::algorithms::SobelGradient("C:\\Users\\t.peruzzi\\Desktop\\test_sobel_img.png");
  gradient.Apply();
}
