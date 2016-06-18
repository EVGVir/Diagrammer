#include "ascii-matrix.h++"
#include <cassert>

using namespace std;


AsciiMatrix::AsciiMatrix():
  mMatrix()
{}


AsciiMatrix::AsciiMatrix(size_t dim_x, size_t dim_y, const unsigned char pattern[]):
  mMatrix()
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
  return *this;
}


unsigned char AsciiMatrix::get(size_t x, size_t y) const {
  if (mMatrix.size()       <= y) return 0;
  if (mMatrix.at(y).size() <= x) return 0;

  return mMatrix.at(y).at(x);
}
