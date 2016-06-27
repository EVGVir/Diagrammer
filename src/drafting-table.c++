#include "drafting-table.h++"


DraftingTable::DraftingTable(size_t width, size_t height, double fontsize) {
  mSurface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
  mContext = cairo_create(mSurface);
  cairo_set_source_rgb(mContext, 1.0, 1.0, 1.0);
  cairo_paint(mContext);
  cairo_set_source_rgb(mContext, 0.0, 0.0, 0.0);
  cairo_select_font_face(mContext, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(mContext, fontsize);

  cairo_font_extents_t fontExtents;
  cairo_font_extents(mContext, &fontExtents);
  mElementWidth  = fontExtents.max_x_advance;
  mElementHeight = fontExtents.height;
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


void DraftingTable::convertCharPosToImageCoordiantes(size_t &x, size_t &y) const {
  x = x * mElementWidth;
  y = y * mElementHeight;
}