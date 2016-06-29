#include "draw.h++"


void drawElement(const DiagramElement &e, DraftingTable &table, size_t x, size_t y) {
  if (e.classes.size() == 0 or
      (e.classes.size() == 1 and e.hasClass(ElementClass::None)))
  {
    table.drawCharacter(x, y, e.c);
    return;
  }

  if (e.hasClass(ElementClass::LineN)) {
    table.drawLineN(x, y);
  }

  if (e.hasClass(ElementClass::LineS)) {
    table.drawLineS(x, y);
  }

  if (e.hasClass(ElementClass::LineE)) {
    table.drawLineE(x, y);
  }

  if (e.hasClass(ElementClass::LineW)) {
    table.drawLineW(x, y);
  }
}
