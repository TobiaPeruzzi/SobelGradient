#include "algorithms/sobelgradient.h"
#include "lib/lodepng.h"

cv::algorithms::SobelGradient::SobelGradient(std::string imgPath, double threshold, bool smoothing)
{
  std::vector<unsigned char> img;
  unsigned int width = 0, height = 0;
  //if decode worked returns 0, otherwise returns 1
  if (lodepng::decode(img, width, height, imgPath))
  {
    std::cout << "Error loading image" << std::endl;
    return;
  }
  _imgArray = types::RGBAMatrix(img, width, height).ConvertGrayscale();
  _threshold = threshold;
  _rows = _imgArray->RowsN();
  _cols = _imgArray->ColumnsN();
  if (smoothing) Smoothing();
}

cv::algorithms::SobelGradient::~SobelGradient()
{
  delete _imgArray;
}

bool cv::algorithms::SobelGradient::Apply()
{
  _result.resize(_rows * _cols * 4);
  int resID = 0;
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      types::Matrix3D* patch = _imgArray->Extract3x3Patch(i, j, true);
      double xConv = 0;
      double yConv = 0;
      SobelConvolution(patch, xConv, yConv);
      double convResTmp = ::sqrt(xConv * xConv + yConv * yConv);
      int convRes; 
      if (convResTmp <= _threshold) convRes = 0;
      else convRes = (int)(convResTmp + 0.5); //rounding the result of convolution
      _result[resID++] = convRes;
      _result[resID++] = convRes;
      _result[resID++] = convRes;
      _result[resID++] = convRes;
      delete patch;
    }
  }
  return true;
}

bool cv::algorithms::SobelGradient::Save(std::string savePath)
{
  if (lodepng::encode(savePath, _result, _cols, _rows))
  {
    std::cout << "Failed Encode" << std::endl;
  }
  return true;
}

void cv::algorithms::SobelGradient::Smoothing()
{
  _smoothing = types::Matrix3D(1, 2, 1, 2, 4, 2, 1, 2, 1);
  _smoothing.Scale(1 / 16.0);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      types::Matrix3D* patch = _imgArray->Extract3x3Patch(i, j, true);
      double smooth = 0;
      SmoothingConvolution(patch, smooth);
      _imgArray->Set(i, j, smooth);
    }
  }
}

void cv::algorithms::SobelGradient::SobelConvolution(types::Matrix3D* patch, double& xConv, double& yConv)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      double value = patch->Get(i, j);
      xConv += value * _Gx.Get(i, j);
      yConv += value * _Gy.Get(i, j);
    }
  }
}

void cv::algorithms::SobelGradient::SmoothingConvolution(types::Matrix3D* patch, double& smooth)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      double value = patch->Get(i, j);
      smooth += value * _smoothing.Get(i, j);
    }
  }
}
