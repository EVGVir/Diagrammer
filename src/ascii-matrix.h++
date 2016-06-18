#pragma once

#include <string>
#include <vector>

/// A storage for an ascii-picture to be converted into an image.
class AsciiMatrix {
public:
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
