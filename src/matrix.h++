#pragma once

#include <vector>


/// 2D array.
template <class T>
class Matrix {
public:
  typedef std::vector<T> Column;    ///< A column of a 2D array.
  typedef std::vector<Column> Data; ///< A 2D array.

  /// Creates a 2D array.
  /// @param width Horizontal size of the created 2D array.
  /// @param height Vertical size of the created 2D array.
  Matrix(std::size_t width, std::size_t height):
    mWidth{width},
    mHeight{height},
    mData(width, Column(height))
  { }

  /// @return Horizontal size of this 2D array.
  std::size_t width() const {
    return mWidth;
  }

  /// @return Vertical size of this 2D array.
  std::size_t height() const {
    return mHeight;
  }

  /// @return A column of data kept in this 2D array. The column's
  /// elements can be accessed by operator [] as well, so the access
  /// to an element can be written as matrix[x][y].
  ///
  /// @param x Index of the column to be returned.
  Column & operator [] (std::size_t x) {
    return mData[x];
  }

private:
  std::size_t mWidth;         ///< Number of columns in this 2D array.
  std::size_t mHeight;        ///< Number of rows in this 2D array.
  Data mData;                 ///< Data kept in this 2D array.
};
