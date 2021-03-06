#pragma once

#include "matrix.h++"
#include <iosfwd>
#include <set>
#include <utility>


/// A diagram element class.
///
/// An element can belong to several classes.
/// @see ElementClasses
enum class ElementClass {
  SolidLineN,         ///< A solid line from the center to the North.
  SolidLineW,         ///< A solid line from the center to the West.
  SolidLineS,         ///< A solid line from the center to the South.
  SolidLineE,         ///< A solid line from the center to the East.
  DashedLineN,        ///< A dashed line from the center to the North.
  DashedLineW,        ///< A dashed line from the center to the West.
  DashedLineS,        ///< A dashed line from the center to the South.
  DashedLineE,        ///< A dashed line from the center to the East.
  ArrowN,             ///< An arrow from the South to the center.
  ArrowS,             ///< An arrow from the North to the center.
  ArrowE,             ///< An arrow from the West to the center.
  ArrowW              ///< An arrow from the East to the center.
};


/// A set of element classes.
typedef std::set<ElementClass> ElementClasses;


/// A digram element: a character and classes assigned to it.
struct DiagramElement {
  char           c;            ///< A character.
  ElementClasses classes;      ///< Classes assigned to the character.

  /// Creates a diagram element.
  ///
  /// @param a_c Character, this element represents.
  /// @param a_classes Classes assigned to the character.
  DiagramElement(char a_c = ' ', ElementClasses &&a_classes = {});

  /// @return Whether a class is assigned to this element.
  ///
  /// @param c Class to be checked.
  ///
  /// @retval true  The class is assigned to this element.
  /// @retval false The class isn't assigned to this element.
  bool hasClass(ElementClass c) const;

  /// @return Whether this element is a character.
  ///
  /// Empty spaces or elements classified as a line are not
  /// characters.
  ///
  /// @retval true  This element is a character.
  /// @retval false This element isn't a character.
  bool isCharacter() const;
};


/// Pattern.
///
/// Patterns are laid down on a diagram. Then it is checked that
/// pattern's characters are equal to corresponding characters in the
/// diagram. If all characters (but 0) are equal then classes from the
/// pattern are applied to diagram's elements.
typedef Matrix<DiagramElement> Pattern;


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
  const Matrix<DiagramElement>::Column & operator [] (size_t x);

  /// @return Horizontal size of this diagram.
  size_t width() const;

  /// @return Vertical size of this diagram.
  size_t height() const;

  /// Checks if the diagram kept in this object is matched to the
  /// provided pattern at a certain position.
  ///
  /// @param pos_x Position to check the patter by X-axis.
  /// @param pos_y Position to check the patter by Y-axis.
  /// @param pattern Pattern to be checked.
  ///
  /// @retval true  Diagram is matched to the pattern.
  /// @retval false Diagram isn't matched to the pattern.
  bool checkPattern(size_t pos_x, size_t pos_y, const Pattern &pattern) const;

  /// Applies a patter to the diagram at a certain position.
  ///
  /// A pattern is applied if corresponding diagram elements include
  /// classes from this pattern.
  ///
  /// @param pos_x Position to apply the patter by X-axis.
  /// @param pos_y Position to apply the patter by Y-axis.
  /// @param pattern Pattern to be applied.
  void applyPatternAtPos(size_t pos_x, size_t pos_y, const Pattern &pattern);

  /// Applies a pattern to the whole diagram.
  ///
  /// @param pattern Pattern to be applied.
  void applyPattern(const Pattern &pattern);

private:
  Matrix<DiagramElement> mMatrix; ///< This diagram's internal data.

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
