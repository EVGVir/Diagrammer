#pragma once

#include <string>
#include <vector>


/// Describes a position in an ascii-picture or pattern.
struct TPoint {
  size_t x;                     ///< X-coordinate.
  size_t y;                     ///< Y-coordinate.
};


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

  /// Looks for a pattern in the picture stored in this object.
  ///
  /// @param pattern Pattern to be found.
  ///
  /// @return Positions of all matches.
  std::vector<TPoint> findPattern(const AsciiMatrix &pattern) const;

  /// @return Width of the picture/pattern stored in this container.
  size_t width() const;

  /// @return Height of the picture/pattern stored in this container.
  size_t height() const;

private:
  typedef std::vector<unsigned char> TRow; ///< Storage for a line of text.
  typedef std::vector<TRow> TMatrix;       ///< Storage for the whole picture/pattern.

  TMatrix mMatrix;                         ///< Storage for the whole picture/pattern.
  size_t  mWidth;                          ///< Picture/pattern width.

  /// Checks if the picture kept in this object is matched to the
  /// provided pattern at a certain position.
  ///
  /// @param pos_x Position to check patter by X-axis.
  /// @param pos_y Position to check patter by Y-axis.
  /// @param pattern Pattern to be checked.
  ///
  /// @retval true  Picture is matched to the pattern.
  /// @retval false Picture is not matched to the pattern.
  bool checkPattern(size_t pos_x, size_t pos_y, const AsciiMatrix &pattern) const;
};
