#include "types/matrix.h"


cv::types::RGBAMatrix::RGBAMatrix()
{
  _rows = 1;
  _cols = 1;
  auto size = (size_t)_rows * _cols;
  _data = new RGBA[size];
  memset(_data, 0, size * sizeof(double));
}

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
  //inverted assignemt because matrix and images are "reversed"
  _rows = columns;
  _cols = rows;
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
  {
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
  }
  return ret;
}

int cv::types::RGBAMatrix::RowsN()
{
  return _rows;
}

int cv::types::RGBAMatrix::ColumnsN()
{
  return _cols;
}

cv::types::RGBAMatrix* cv::types::RGBAMatrix::Extract3x3Patch(int centerRow, int centerColumn, bool padding)
{
  //if no padding is required and the center lies on an edge, return null
  if (!padding && (centerRow == 0 || centerColumn == 0 || centerRow == _rows - 1 || centerRow == _cols - 1)) return 0x00;
  RGBAMatrix* patch = new RGBAMatrix(3, 3);
  int patchRowId = 0;
  if (Padding(centerRow, centerColumn, patch)) return patch;
  for (int i = centerRow - 1; i <= centerRow + 1; i++)
  {
    int patchColId = 0;
    for (int j = centerColumn - 1; j <= centerColumn + 1; j++)
    {
      patch->Set(patchRowId, patchColId++, Get(i, j));
    }
    patchRowId++;
  }
  return patch;
}

cv::types::Matrix* cv::types::RGBAMatrix::ConvertGrayscale()
{
  Matrix* ret = new Matrix(_rows, _cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      types::RGBA rgbaValue = Get(i, j);
      //using weighted conversion from rgba to grayscale. The A value is lost in the conversion
      ret->Set(i, j, 0.299 * rgbaValue.R + 0.587 * rgbaValue.G + 0.114 * rgbaValue.B);
    }
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

bool cv::types::RGBAMatrix::Padding(int& centerRow, int& centerColumn, RGBAMatrix* data)
{
  if (centerRow == 0 && centerColumn != 0 && centerColumn != _cols - 1)
  {
    int prevCol = centerColumn - 1;
    int nextCol = centerColumn + 1;
    data->Set(0, 0, Get(0, prevCol));
    data->Set(0, 1, Get(0, centerColumn));
    data->Set(0, 2, Get(0, nextCol));
    data->Set(1, 0, Get(0, prevCol));
    data->Set(1, 1, Get(0, centerColumn));
    data->Set(1, 2, Get(0, nextCol));
    data->Set(2, 0, Get(1, prevCol));
    data->Set(2, 1, Get(1, centerColumn));
    data->Set(2, 2, Get(1, nextCol));
    return true;
  }
  if (centerRow == 0 && centerColumn == 0)
  {
    data->Set(0, 0, Get(0, 0));
    data->Set(0, 1, Get(0, 0));
    data->Set(0, 2, Get(0, 1));
    data->Set(1, 0, Get(0, 0));
    data->Set(1, 1, Get(0, 0));
    data->Set(1, 2, Get(0, 1));
    data->Set(2, 0, Get(1, 0));
    data->Set(2, 1, Get(1, 0));
    data->Set(2, 2, Get(1, 1));
    return true;
  }
  if (centerRow == 0 && centerColumn == _cols - 1)
  {
    int prevCol = centerColumn - 1;
    data->Set(0, 0, Get(0, prevCol));
    data->Set(0, 1, Get(0, centerColumn));
    data->Set(0, 2, Get(0, centerColumn));
    data->Set(1, 0, Get(0, prevCol));
    data->Set(1, 1, Get(0, centerColumn));
    data->Set(1, 2, Get(0, centerColumn));
    data->Set(2, 0, Get(1, prevCol));
    data->Set(2, 1, Get(1, centerColumn));
    data->Set(2, 2, Get(1, centerColumn));
    return true;
  }
  if (centerColumn == 0 && centerRow != 0 && centerRow != _rows - 1)
  {
    int prevRow = centerRow - 1;
    int nextRow = centerRow + 1;
    data->Set(0, 0, Get(prevRow, 0));
    data->Set(0, 1, Get(prevRow, 0));
    data->Set(0, 2, Get(prevRow, 1));
    data->Set(0, 0, Get(centerRow, 0));
    data->Set(0, 1, Get(centerRow, 0));
    data->Set(0, 2, Get(centerRow, 1));
    data->Set(0, 0, Get(nextRow, 0));
    data->Set(0, 1, Get(nextRow, 0));
    data->Set(0, 2, Get(nextRow, 1));
    return true;
  }
  if (centerColumn == 0 && centerRow == _rows - 1)
  {
    int prevRow = centerRow - 1;
    data->Set(0, 0, Get(prevRow, 0));
    data->Set(0, 1, Get(prevRow, 0));
    data->Set(0, 2, Get(prevRow, 1));
    data->Set(0, 0, Get(centerRow, 0));
    data->Set(0, 1, Get(centerRow, 0));
    data->Set(0, 2, Get(centerRow, 1));
    data->Set(0, 0, Get(centerRow, 0));
    data->Set(0, 1, Get(centerRow, 0));
    data->Set(0, 2, Get(centerRow, 1));
    return true;
  }
  if (centerRow == _rows - 1 && centerColumn != 0 && centerColumn != _cols - 1)
  {
    int prevRow = centerRow - 1;
    int prevCol = centerColumn - 1;
    int nextCol = centerColumn + 1;
    data->Set(0, 0, Get(prevRow, prevCol));
    data->Set(0, 1, Get(prevRow, centerColumn));
    data->Set(0, 2, Get(prevRow, nextCol));
    data->Set(0, 0, Get(centerRow, prevCol));
    data->Set(0, 1, Get(centerRow, centerColumn));
    data->Set(0, 2, Get(centerRow, nextCol));
    data->Set(0, 0, Get(centerRow, prevCol));
    data->Set(0, 1, Get(centerRow, centerColumn));
    data->Set(0, 2, Get(centerRow, nextCol));
    return true;
  }
  if (centerRow == _rows - 1 && centerColumn == _cols - 1)
  {
    int prevRow = centerRow - 1;
    int prevCol = centerColumn - 1;
    data->Set(0, 0, Get(prevRow, prevCol));
    data->Set(0, 1, Get(prevRow, centerColumn));
    data->Set(0, 2, Get(prevRow, centerColumn));
    data->Set(0, 0, Get(centerRow, prevCol));
    data->Set(0, 1, Get(centerRow, centerColumn));
    data->Set(0, 2, Get(centerRow, centerColumn));
    data->Set(0, 0, Get(centerRow, prevCol));
    data->Set(0, 1, Get(centerRow, centerColumn));
    data->Set(0, 2, Get(centerRow, centerColumn));
    return true;
  }
  return false;
}
