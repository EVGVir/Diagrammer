#include "ascii-matrix.h++"
#include <cassert>
#include <algorithm>

using std::max;
using std::string;


AsciiMatrix::AsciiMatrix():
  mMatrix(), mWidth(0)
{}


AsciiMatrix::AsciiMatrix(size_t dim_x, size_t dim_y, const unsigned char pattern[]):
  mMatrix(), mWidth(dim_x)
{
  for (size_t y = 0; y < dim_y; ++y) {
    TRow row;
    for (size_t x = 0; x < dim_x; ++x) {
      row.push_back(pattern[x + y * dim_x]);
    }
    mMatrix.push_back(row);
  }
}


AsciiMatrix & AsciiMatrix::operator << (const string &input) {
  TRow row(input.begin(), input.end());
  mMatrix.push_back(row);
  mWidth = max(mWidth, row.size());
  return *this;
}


unsigned char AsciiMatrix::get(size_t x, size_t y) const {
  if (mMatrix.size()       <= y) return 0;
  if (mMatrix.at(y).size() <= x) return 0;

  return mMatrix.at(y).at(x);
}


size_t AsciiMatrix::width() const {
  return mWidth;
}


size_t AsciiMatrix::height() const {
  return mMatrix.size();
}
