#include <iostream>
#include "algorithms/sobelgradient.h"


int main()
{
  auto gradient = cv::algorithms::SobelGradient("", 100, true);
  gradient.Apply();
  gradient.Save("");
}
