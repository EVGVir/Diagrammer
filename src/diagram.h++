#pragma once

#include "matrix.h++"
#include <iosfwd>
#include <utility>


/// An ASCII-diagram.
class Diagram {
public:
  /// Constructs a diagram by using characters from a stream.
  ///
  /// @param input A stream which contains an ASCII-diagram to be
  ///   processed.
  ///
  /// @todo The method should not work correct with a partly read
  ///   streams.
  Diagram(std::istream &input);

  /// @return A column of data kept in this diagram. The column's
  /// elements can be accessed by operator [] as well, so the access
  /// to a diagram element can be written as diagram[x][y].
  ///
  /// @param x Index of the column to be returned.
  const Matrix<unsigned char>::Column & operator [] (size_t x);

  /// @return Horizontal size of this diagram.
  size_t width() const;

  /// @return Vertical size of this diagram.
  size_t height() const;

private:
  Matrix<unsigned char> mMatrix; ///< This diagram's internal data.

  /// @return Dimensions (width, height) of a digram which is kept in
  /// the stream.
  ///
  /// @param input A stream which contains an ASCII-diagram to be
  ///   processed.
  ///
  /// @warning The method rewind the stream to the very beginning, so
  /// it is unsuatable to be used with a partly read streams.
  std::pair<size_t, size_t> getDimensions(std::istream &input);
};
