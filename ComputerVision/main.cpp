#include <iostream>
#include "algorithms/sobelgradient.h"


int main()
{
  auto gradient = cv::algorithms::SobelGradient("C:\\Users\\t.peruzzi\\Desktop\\Valve_original_(1).png", 20, true);
  gradient.Apply();
  gradient.Save("C:\\Users\\t.peruzzi\\Desktop\\testConv2.png");
}
