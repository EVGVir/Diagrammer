#pragma once

#include <cairo.h>
#include <string>


/// Draws a diagram element by element.
///
/// @note Position in number of characters (from left to right and
/// from top to bottom) is taken as methods parameters if not said
/// other.
class DraftingTable {
public:
  /// @param width Diagram's width in number of characters.
  /// @param height Diagram's height in number of characters.
  /// @param fontsize Size of the font to draw the diagram in Cairo
  ///   units.
  DraftingTable(size_t width, size_t height, double fontsize);
  virtual ~DraftingTable();

  /// Saves the drawn diagram into a PNG-file.
  ///
  /// @param filename File to save the diagram into.
  virtual void saveToPNG(const std::string &filename) const;

  /// Draws a character.
  ///
  /// @param x Character to be drawn horizontal position.
  /// @param y Character to be drawn vertical position.
  /// @param c Character to be drawn.
  virtual void drawCharacter(size_t x, size_t y, char c);

  /// Draws a solid line from the element's center to the North.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawSolidLineN(size_t x, size_t y);

  /// Draws a solid line from the element's center to the South.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawSolidLineS(size_t x, size_t y);

  /// Draws a solid line from the element's center to the East.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawSolidLineE(size_t x, size_t y);

  /// Draws a solid line from the element's center to the West.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawSolidLineW(size_t x, size_t y);

  /// Draws a dashed line from the element's center to the North.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawDashedLineN(size_t x, size_t y);

  /// Draws a dashed line from the element's center to the South.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawDashedLineS(size_t x, size_t y);

  /// Draws a dashed line from the element's center to the East.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawDashedLineE(size_t x, size_t y);

  /// Draws a dashed line from the element's center to the West.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawDashedLineW(size_t x, size_t y);

  /// Draws an arrow to the element's center from the South.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowNtoCenter(size_t x, size_t y);

  /// Draws an arrow to the element's center from the North.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowStoCenter(size_t x, size_t y);

  /// Draws an arrow to the element's center from the West.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowEtoCenter(size_t x, size_t y);

  /// Draws an arrow to the element's center from the East.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowWtoCenter(size_t x, size_t y);

  /// Draws an arrow to the element's edge from the South.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowNtoEdge(size_t x, size_t y);

  /// Draws an arrow to the element's edge from the North.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowStoEdge(size_t x, size_t y);

  /// Draws an arrow to the element's edge from the West.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowEtoEdge(size_t x, size_t y);

  /// Draws an arrow to the element's edge from the East.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  virtual void drawArrowWtoEdge(size_t x, size_t y);

  /// Draws horizontal and vertical lines all over the resulting
  /// picture. The distance between lines is equal to maximum
  /// characters dimensions.
  virtual void drawMesh();

private:
  /// Styles for drawing lines.
  enum class LineStyle {
    Solid,                      ///< Solid line.
    Dashed                      ///< Dashed line.
  };

  size_t           mElementWidth;  ///< Width of an element in Cairo units.
  size_t           mElementHeight; ///< Height of an element in Cairo units.
  double           mArrowLength;   ///< Length of an arrow in Cairo units.
  double           mArrowWidth;    ///< Width of an arrow in Cairo units.
  cairo_surface_t *mSurface;       ///< Cairo's easel where diagram is drawn.
  cairo_t         *mContext;       ///< Cairo's context.

  /// Draws a line from [from_x; from_y] to [to_x; to_y].
  ///
  /// @param from_x Horizontal coordinate, the line must be drawn from.
  /// @param from_y Vertical coordinate, the line must be drawn from.
  /// @param to_x Horizontal coordinate, the line must be drawn to.
  /// @param to_y Vertical coordinate, the line must be drawn to.
  /// @param style Style, the line must be drawn of.
  void drawLine(double from_x, double from_y, double to_x, double to_y, LineStyle style);

  /// Draws an arrow that points to the [x; y].
  ///
  /// @param x Horizontal coordinate, the arrow must point to.
  /// @param y Vertical coordinate, the arrow must point to.
  /// @param angle Angle (in radians), the arrow must be rotated by.
  ///   0 - arrow points from South to North. The angle is increasing
  ///   in counter clockwise direction.
  void drawArrow(double x, double y, double angle);

  /// Converts a character position to Cairo units in place (replaces
  /// input parameters by result).
  ///
  /// @param[in,out] x Horizontal position to be converted.
  /// @param[in,out] y Vertical position to be converted.
  void convertCharPosToImageCoordiantes(size_t &x, size_t &y) const;

  /// @return Font extents for desired fontsize.
  /// @param fontsize Size of the font to get it extents, in Cairo
  ///   units.
  cairo_font_extents_t getFontExtents(double fontsize) const;
};
