#pragma once

#include <string>
#include <vector>

/// A storage for an ascii-picture to be converted into an image or
/// a pattern.
class AsciiMatrix {
public:
  /// Creates an empty storage.
  AsciiMatrix();

  /// Initializes the storage with the provided pattern.
  ///
  /// @param dim_x Pattern dimension by the X-axis.
  /// @param dim_y Pattern dimension by the Y-axis.
  /// @param pattern Initialization pattern (a 2D array written as
  ///   a 1D array row by row).
  AsciiMatrix(size_t dim_x, size_t dim_y, const unsigned char pattern[]);

  /// Appends a string into the storage.
  ///
  /// @param input String to be added into the storage.
  ///
  /// @return This storage, so several operations can be chained.
  AsciiMatrix & operator << (const std::string &input);

  /// @return Character located on the desired position.
  ///
  /// @param x X-coordinate of the character to be returned.
  /// @param y Y-coordinate of the character to be returned.
  ///
  /// @retval 0 A coordinate is bigger than corresponding
  ///   ascii-picture dimension.
  unsigned char get(size_t x, size_t y) const;

private:
  typedef std::vector<unsigned char> TRow; ///< Storage for a line of text.
  typedef std::vector<TRow> TMatrix;       ///< Storage for the whole picture.

  TMatrix mMatrix;                         ///< Storage for the whole picture.
};
