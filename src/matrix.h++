#pragma once

#include <algorithm>
#include <vector>


/// 2D array.
template <class T>
class Matrix {
public:
  typedef std::vector<T> Column;    ///< A column of a 2D array.
  typedef std::vector<Column> Data; ///< A 2D array.

  /// Creates a 2D array.
  ///
  /// @param width Horizontal size of the created 2D array.
  ///
  /// @param height Vertical size of the created 2D array.
  Matrix(std::size_t width, std::size_t height):
    mWidth{width},
    mHeight{height},
    mData(width, Column(height))
  { }


  /// Creates a 2D array.
  ///
  /// @param data Initialization data row-by-row.
  ///
  /// @warning Althoug the internal data representation is
  /// column-by-column, in sake of convenience data parameter is
  /// row-by-row:
  ///        0   1   2        X
  ///   +----+---+---+--------->
  ///   | Matrix<int> matrix{{
  /// 0 +   {00, 10, 20},
  ///   |
  /// 1 +   {01, 11, 21}
  ///   | }}
  ///   |
  ///   v Y
  Matrix(const Data &data):
    mWidth{0},
    mHeight{data.size()}
  {
    for (auto &row: data) {
      mWidth = std::max(mWidth, row.size());
    }

    mData = Data(mWidth, Column(mHeight));

    for (size_t x = 0; x < mWidth; ++x) {
      for (size_t y = 0; y < mHeight; ++y) {
        // Transpose the matrix, as it is written a row by row.
        mData[x][y] = data[y][x];
      }
    }
  }

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

  /// Const version of operator [].
  const Column & operator [] (std::size_t x) const {
    return mData[x];
  }

private:
  std::size_t mWidth;         ///< Number of columns in this 2D array.
  std::size_t mHeight;        ///< Number of rows in this 2D array.
  Data mData;                 ///< Data kept in this 2D array.
};
