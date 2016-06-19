#include "ascii-matrix.h++"
#include <cassert>
#include <algorithm>

using std::max;
using std::string;
using std::vector;


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


vector<TPoint> AsciiMatrix::findPattern(const AsciiMatrix &pattern) const {
  vector<TPoint> result;

  if (pattern.width() > width() ||
      pattern.height() > height())
  {
    return result;
  }

  for (size_t x = 0; x <= width() - pattern.width(); ++x) {
    for (size_t y = 0; y <= height() - pattern.height(); ++y) {
      if (checkPattern(x, y, pattern)) {
        result.push_back({x, y});
      }
    }
  }

  return result;
}


size_t AsciiMatrix::width() const {
  return mWidth;
}


size_t AsciiMatrix::height() const {
  return mMatrix.size();
}


bool AsciiMatrix::checkPattern(size_t pos_x, size_t pos_y, const AsciiMatrix &pattern) const {
  if (pos_x + pattern.width()  > width() ||
      pos_y + pattern.height() > height())
  {
    return false;
  }

  for (size_t pat_x = 0; pat_x < pattern.width(); ++pat_x) {
    for (size_t pat_y = 0; pat_y < pattern.height(); ++pat_y) {
      unsigned char pat_value = pattern.get(pat_x, pat_y);

      if (pat_value != 0 &&
          pat_value != get(pos_x + pat_x, pos_y + pat_y))
      {
        return false;
      }
    }
  }

  return true;
}
