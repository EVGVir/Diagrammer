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
 ~DraftingTable();

  /// Saves the drawn diagram into a PNG-file.
  ///
  /// @param filename File to save the diagram into.
  void saveToPNG(const std::string &filename) const;

  /// Draws a character.
  ///
  /// @param x Character to be drawn horizontal position.
  /// @param y Character to be drawn vertical position.
  /// @param c Character to be drawn.
  void drawCharacter(size_t x, size_t y, char c);

  /// Draws a line from the element's center to the North.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  void drawLineN(size_t x, size_t y);

  /// Draws a line from the element's center to the South.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  void drawLineS(size_t x, size_t y);

  /// Draws a line from the element's center to the East.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  void drawLineE(size_t x, size_t y);

  /// Draws a line from the element's center to the West.
  ///
  /// @param x Element to be drawn horizontal position.
  /// @param y Element to be drawn vertical position.
  void drawLineW(size_t x, size_t y);

private:
  size_t           mElementWidth;  ///< Width of an element in Cairo units.
  size_t           mElementHeight; ///< Height of an element in Cairo units.
  cairo_surface_t *mSurface;       ///< Cairo's easel where diagram is drawn.
  cairo_t         *mContext;       ///< Cairo's context.

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
