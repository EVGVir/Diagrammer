#include "drafting-table.h++"

#include <algorithm>

using std::max;


static const double PI = 3.141592653589793238462643383279502884197169399375105820974;


DraftingTable::DraftingTable(size_t width, size_t height, double fontsize) {
  auto fontExtents = getFontExtents(fontsize);

  mElementWidth  = fontExtents.max_x_advance;
  mElementHeight = fontExtents.height;

  mArrowLength = max(mElementWidth, mElementHeight);
  mArrowWidth  = mArrowLength / 2;

  mSurface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width * mElementWidth, height * mElementHeight);
  mContext = cairo_create(mSurface);
  cairo_set_source_rgb(mContext, 1.0, 1.0, 1.0);
  cairo_paint(mContext);
  cairo_set_source_rgb(mContext, 0.0, 0.0, 0.0);
  cairo_select_font_face(mContext, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(mContext, fontsize);
}


DraftingTable::~DraftingTable() {
  cairo_destroy(mContext);
  cairo_surface_destroy(mSurface);
}


void DraftingTable::saveToPNG(const std::string &filename) const {
  cairo_surface_write_to_png(mSurface, filename.c_str());
}


void DraftingTable::drawCharacter(size_t x, size_t y, char c) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_move_to(mContext, x, y + mElementHeight);
  cairo_show_text(mContext, std::string(1, c).c_str());
}


void DraftingTable::drawLineN(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_move_to(mContext, x + mElementWidth / 2, y + mElementHeight / 2);
  cairo_line_to(mContext, x + mElementWidth / 2, y);
  cairo_stroke(mContext);
}


void DraftingTable::drawLineS(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_move_to(mContext, x + mElementWidth / 2, y + mElementHeight / 2);
  cairo_line_to(mContext, x + mElementWidth / 2, y + mElementHeight);
  cairo_stroke(mContext);
}


void DraftingTable::drawLineE(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_move_to(mContext, x + mElementWidth / 2, y + mElementHeight / 2);
  cairo_line_to(mContext, x + mElementWidth,     y + mElementHeight / 2);
  cairo_stroke(mContext);
}


void DraftingTable::drawLineW(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_move_to(mContext, x + mElementWidth / 2, y + mElementHeight / 2);
  cairo_line_to(mContext, x,                     y + mElementHeight / 2);
  cairo_stroke(mContext);
}


void DraftingTable::drawArrowN(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_translate(mContext, x + 0.5 * mElementWidth, y + 0.5 * mElementHeight);
  drawArrow();
  cairo_identity_matrix(mContext);
}


void DraftingTable::drawArrowS(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_translate(mContext, x + 0.5 * mElementWidth, y + 0.5 * mElementHeight);
  cairo_rotate(mContext, PI);
  drawArrow();
  cairo_identity_matrix(mContext);
}


void DraftingTable::drawArrowE(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_translate(mContext, x + 0.5 * mElementWidth, y + 0.5 * mElementHeight);
  cairo_rotate(mContext, 0.5 * PI);
  drawArrow();
  cairo_identity_matrix(mContext);
}


void DraftingTable::drawArrowW(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  cairo_translate(mContext, x + 0.5 * mElementWidth, y + 0.5 * mElementHeight);
  cairo_rotate(mContext, -0.5 * PI);
  drawArrow();
  cairo_identity_matrix(mContext);
}


void DraftingTable::drawArrow() {
  cairo_move_to(mContext,               0.0,           0.0);
  cairo_line_to(mContext, 0.5 * mArrowWidth,  mArrowLength);
  cairo_curve_to(mContext,
                   0.5 * mArrowWidth,       mArrowLength,
                                 0.0, 0.6 * mArrowLength,
                 - 0.5 * mArrowWidth,       mArrowLength);
  cairo_fill(mContext);
}


void DraftingTable::convertCharPosToImageCoordiantes(size_t &x, size_t &y) const {
  x = x * mElementWidth;
  y = y * mElementHeight;
}


cairo_font_extents_t DraftingTable::getFontExtents(double fontsize) const {
  cairo_font_extents_t result;

  auto tmpSurface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 0, 0);
  auto tmpContext = cairo_create(tmpSurface);
  cairo_select_font_face(tmpContext, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(tmpContext, fontsize);
  cairo_font_extents(tmpContext, &result);
  cairo_destroy(tmpContext);
  cairo_surface_destroy(tmpSurface);

  return result;
}
