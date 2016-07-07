#include "drafting-table.h++"
#include "context-guard.h++"

#include <algorithm>

using std::max;
using std::min;


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
  ContextGuard guard{mContext};
  convertCharPosToImageCoordiantes(x, y);
  cairo_move_to(mContext, x, y + mElementHeight);
  cairo_show_text(mContext, std::string(1, c).c_str());
}


void DraftingTable::drawSolidLineN(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x + mElementWidth / 2, y + mElementHeight / 2,
           x + mElementWidth / 2, y,
           LineStyle::Solid);
}


void DraftingTable::drawSolidLineS(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x + mElementWidth / 2, y + mElementHeight / 2,
           x + mElementWidth / 2, y + mElementHeight,
           LineStyle::Solid);
}


void DraftingTable::drawSolidLineE(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x + mElementWidth / 2, y + mElementHeight / 2,
           x + mElementWidth,     y + mElementHeight / 2,
           LineStyle::Solid);
}


void DraftingTable::drawSolidLineW(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x + mElementWidth / 2, y + mElementHeight / 2,
           x,                     y + mElementHeight / 2,
           LineStyle::Solid);
}


void DraftingTable::drawDashedLineN(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x + mElementWidth / 2, y,
           x + mElementWidth / 2, y + mElementHeight / 2,
           LineStyle::Dashed);
}


void DraftingTable::drawDashedLineS(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x + mElementWidth / 2, y + mElementHeight / 2,
           x + mElementWidth / 2, y + mElementHeight,
           LineStyle::Dashed);
}


void DraftingTable::drawDashedLineE(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x + mElementWidth / 2, y + mElementHeight / 2,
           x + mElementWidth,     y + mElementHeight / 2,
           LineStyle::Dashed);
}


void DraftingTable::drawDashedLineW(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawLine(x,                     y + mElementHeight / 2,
           x + mElementWidth / 2, y + mElementHeight / 2,
           LineStyle::Dashed);
}


void DraftingTable::drawArrowNtoCenter(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x + 0.5 * mElementWidth, y + 0.5 * mElementHeight, 0);
}


void DraftingTable::drawArrowStoCenter(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x + 0.5 * mElementWidth, y + 0.5 * mElementHeight, PI);
}


void DraftingTable::drawArrowEtoCenter(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x + 0.5 * mElementWidth, y + 0.5 * mElementHeight, -0.5 * PI);
}


void DraftingTable::drawArrowWtoCenter(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x + 0.5 * mElementWidth, y + 0.5 * mElementHeight, 0.5 * PI);
}


void DraftingTable::drawArrowNtoEdge(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x + 0.5 * mElementWidth, y + mElementHeight, 0);
}


void DraftingTable::drawArrowStoEdge(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x + 0.5 * mElementWidth, y, PI);
}


void DraftingTable::drawArrowEtoEdge(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x, y + 0.5 * mElementHeight, -0.5 * PI);
}


void DraftingTable::drawArrowWtoEdge(size_t x, size_t y) {
  convertCharPosToImageCoordiantes(x, y);
  drawArrow(x + mElementWidth, y + 0.5 * mElementHeight, 0.5 * PI);
}


void DraftingTable::drawLine(double from_x, double from_y, double to_x, double to_y, LineStyle style) {
  ContextGuard guard{mContext};
  cairo_move_to(mContext, from_x, from_y);
  cairo_line_to(mContext, to_x,   to_y);

  if (style == LineStyle::Dashed) {
    double dashes[] = {double(min(mElementWidth, mElementHeight)) / 2};
    cairo_set_dash(mContext, dashes, sizeof(dashes) / sizeof(double), from_x + from_y);
  }

  cairo_stroke(mContext);
}


void DraftingTable::drawArrow(double x, double y, double angle) {
  ContextGuard guard{mContext};

  cairo_translate(mContext, x, y);
  cairo_rotate(mContext, -angle);

  cairo_move_to(mContext,               0.0,           0.0);
  cairo_line_to(mContext, 0.5 * mArrowWidth,  mArrowLength);
  cairo_curve_to(mContext,
                   0.5 * mArrowWidth,       mArrowLength,
                                 0.0, 0.6 * mArrowLength,
                 - 0.5 * mArrowWidth,       mArrowLength);
  cairo_fill(mContext);
}


void DraftingTable::drawMesh() {
  ContextGuard guard{mContext};
  int width = cairo_image_surface_get_width(mSurface);
  int height = cairo_image_surface_get_height(mSurface);

  for (int y = mElementHeight; y < height; y += mElementHeight) {
    cairo_move_to(mContext, 0, y);
    cairo_line_to(mContext, width, y);
  }

  for (int x = mElementWidth; x < width; x += mElementWidth) {
    cairo_move_to(mContext, x, 0);
    cairo_line_to(mContext, x, height);
  }

  cairo_set_source_rgb(mContext, 0.6, 0.6, 0.6);
  cairo_set_line_width(mContext, 0.5);
  cairo_stroke(mContext);
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
