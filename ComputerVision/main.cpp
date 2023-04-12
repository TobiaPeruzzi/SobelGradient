#include <iostream>
#include "algorithms/sobelgradient.h"


int main()
{
  auto gradient = cv::algorithms::SobelGradient("C:\\Users\\t.peruzzi\\Desktop\\phone_img.png", 100, true);
  gradient.Apply();
  gradient.Save("C:\\Users\\t.peruzzi\\Desktop\\conv_phone_img_2.png");
}
