#include "types/matrix.h"


cv::types::RGBAMatrix::RGBAMatrix(int rows, int columns)
{
  _rows = rows;
  _cols = columns;
  auto size = (size_t)_rows * _cols;
  _data = new RGBA[size];
  memset(_data, 0, size * sizeof(double));
}

cv::types::RGBAMatrix::RGBAMatrix(std::vector<unsigned char> data, int rows, int columns)
{
  _rows = rows;
  _cols = columns;
  auto size = (size_t)_rows * _cols;
  _data = new RGBA[size];
  int rowInd = 0;
  int colInd = 0;
  for (int i = 0; i < data.size(); i+=4)
  {
    RGBA value = RGBA(data[i], data[i + 1], data[i + 2], data[i + 3]);
    if (colInd == _cols)
    {
      rowInd++;
      colInd = 0;
    }
    Set(rowInd, colInd, value);
    colInd++;
  }
}

bool cv::types::RGBAMatrix::Set(int row, int column, RGBA value)
{
  RangeCheck(row, column);
  _data[row * _cols + column] = value;
  return true;
}

cv::types::RGBA cv::types::RGBAMatrix::Get(int row, int column)
{
  RangeCheck(row, column);
  return _data[row * _cols + column];
}

std::vector<unsigned char> cv::types::RGBAMatrix::GetImgOutput()
{
  //vector size multiplied by 4 because every matrix entry only corresponds to an r, b, g or a value
  std::vector<unsigned char> ret(_rows * _cols * 4);
  int imgInd = 0;
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++)
    {
      auto rgbaPx = Get(i, j);
      ret[imgInd] = rgbaPx.R;
      imgInd++;
      ret[imgInd] = rgbaPx.G;
      imgInd++;
      ret[imgInd] = rgbaPx.B;
      imgInd++;
      ret[imgInd] = rgbaPx.A;
      imgInd++;
    }
  return ret;
}

bool cv::types::RGBAMatrix::Resize(int rows, int columns)
{
  auto size = (size_t)rows * columns;
  size_t oldSize = (size_t)(_rows * _cols);
  if (size == oldSize)  return true;
  auto newMatrix = RGBAMatrix(rows, columns);
  if (size > oldSize)
  {
    //todo: refactor with vectorization or memcopy
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++)
        newMatrix.Set(i, j, Get(i, j));
  }
  else // size < oldSize
  {
    int tmpRows = std::min(rows, _rows);
    int tmpCols = std::min(columns, _cols);
    //todo: refactor with vectorization
    for (int i = 0; i < tmpRows; i++)
      for (int j = 0; j < tmpCols; j++)
        newMatrix.Set(i, j, Get(i, j));
  }
  _rows = rows;
  _cols = columns;
  _data = newMatrix._data;
  return true;
}

void cv::types::RGBAMatrix::RangeCheck(int& i, int& j)
{
  if (i < 0) i = 0;
  if (j < 0) j = 0;
  if (i >= _rows) i = _rows - 1;
  if (j >= _cols) j = _cols - 1;
}
