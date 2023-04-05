#include "algorithms/sobelgradient.h"

cv::algorithms::SobelGradient::SobelGradient(types::Matrix img)
{
  _imgArray = img;
}

bool cv::algorithms::SobelGradient::Apply()
{
  auto convImg = types::Matrix(_imgArray.RowN(), _imgArray.ColumnsN());

}
