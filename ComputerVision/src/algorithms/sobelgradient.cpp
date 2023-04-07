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
  _imgArray = types::RGBAMatrix(img, width, height);
}

bool cv::algorithms::SobelGradient::Apply()
{
  int rows = _imgArray.RowsN();
  int cols = _imgArray.ColumnsN();
  std::vector<unsigned char> result(rows * cols * 4);
  types::RGBA xConv;
  types::RGBA yConv;
  int resID = 0;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      types::RGBAMatrix* testPad = _imgArray.Extract3x3Patch(i, j, true);
      types::RGBA xConv;
      types::RGBA yConv;
      Convolution(testPad, xConv, yConv);
      result[resID++] = xConv.R;
      result[resID++] = xConv.G;
      result[resID++] = xConv.B;
      result[resID++] = xConv.A;
      delete testPad;
    }
  }
  std::string testPadPath = "C:\\Users\\t.peruzzi\\Desktop\\testConv.png";
  if (lodepng::encode(testPadPath, result, cols, rows))
  {
    std::cout << "Failed Encode" << std::endl;
  }
  return true;
}

void cv::algorithms::SobelGradient::Convolution(types::RGBAMatrix* patch, types::RGBA& xConv, types::RGBA& yConv)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      types::RGBA tmpPtX = patch->Get(i, j);
      types::RGBA tmpPtY = tmpPtX;
      tmpPtX.Scale(_Gx.Get(i, j));
      xConv.Sum(tmpPtX);
      tmpPtY.Scale(_GY.Get(i, j));
      yConv.Sum(tmpPtY);
    }
  }
}
