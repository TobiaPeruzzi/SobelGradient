#include "algorithms/sobelgradient.h"
#include "lib/lodepng.h"

cv::algorithms::SobelGradient::SobelGradient(std::string imgPath)
{
  std::vector<unsigned char> img;
  unsigned int width = 0, height = 0;
  //if decode worked returns 0, otherwise returns 1
  if (lodepng::decode(img, width, height, imgPath))
  {
    std::cout << "Error loading image" << std::endl;
    return;
  }
  auto imgMatrix = types::RGBAMatrix(img, width, height);
  auto imgVec = imgMatrix.GetImgOutput();
  std::string outPath = "C:\\Users\\t.peruzzi\\Desktop\\testThingPng.png";
  if (lodepng::encode(outPath, imgVec, width, height))
  {
    std::cout << "Error encoding" << std::endl;
  }
}

bool cv::algorithms::SobelGradient::Apply()
{
  auto convImg = types::Matrix(_imgArray.RowN(), _imgArray.ColumnsN());
  return true;
}
