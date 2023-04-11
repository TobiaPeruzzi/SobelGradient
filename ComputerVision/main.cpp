#include <iostream>
#include "algorithms/sobelgradient.h"


int main()
{
  auto gradient = cv::algorithms::SobelGradient("", 20, true);
  gradient.Apply();
  gradient.Save("");
}
