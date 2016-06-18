#include "ascii-matrix.h++"
#include <cassert>

using namespace std;


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
