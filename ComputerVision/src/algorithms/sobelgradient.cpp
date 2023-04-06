#include "algorithms/sobelgradient.h"
#include "lib/lodepng.h"

cv::algorithms::SobelGradient::SobelGradient(std::string imgPath)
{
  std::vector<unsigned char> img;
  unsigned int width = 0, height = 0;
  //if decode worked returns 0
  if (!lodepng::decode(img, width, height, imgPath))
  {
    std::cout << width << std::endl;
    std::cout << height << std::endl;
    std::string savePath = "C:\\Users\\t.peruzzi\\Desktop\\testEncode.png";
    lodepng::encode(savePath, img, width, height);
  }
}

bool cv::algorithms::SobelGradient::Apply()
{
  auto convImg = types::Matrix(_imgArray.RowN(), _imgArray.ColumnsN());
  return true;
}
