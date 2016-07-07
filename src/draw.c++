#include "draw.h++"


void drawDiagram(Diagram &diagram, DraftingTable &table) {
  for (size_t x = 0; x < diagram.width(); ++x) {
    for (size_t y = 0; y < diagram.height(); ++y) {
      drawElement(diagram[x][y], table, x, y);
    }
  }
}


void drawElement(const DiagramElement &e, DraftingTable &table, size_t x, size_t y) {
  if (e.classes.size() == 0) {
    table.drawCharacter(x, y, e.c);
    return;
  }

  if (e.hasClass(ElementClass::SolidLineN)) {
    table.drawSolidLineN(x, y);
  }

  if (e.hasClass(ElementClass::SolidLineS)) {
    table.drawSolidLineS(x, y);
  }

  if (e.hasClass(ElementClass::SolidLineE)) {
    table.drawSolidLineE(x, y);
  }

  if (e.hasClass(ElementClass::SolidLineW)) {
    table.drawSolidLineW(x, y);
  }

  if (e.hasClass(ElementClass::DashedLineN)) {
    table.drawDashedLineN(x, y);
  }

  if (e.hasClass(ElementClass::DashedLineS)) {
    table.drawDashedLineS(x, y);
  }

  if (e.hasClass(ElementClass::DashedLineE)) {
    table.drawDashedLineE(x, y);
  }

  if (e.hasClass(ElementClass::DashedLineW)) {
    table.drawDashedLineW(x, y);
  }

  if (e.hasClass(ElementClass::ArrowN)) {
    if (!e.isCharacter()) {
      table.drawArrowNtoCenter(x, y);
    } else {
      table.drawCharacter(x, y, e.c);
      table.drawArrowNtoEdge(x, y);
    }
  }

  if (e.hasClass(ElementClass::ArrowS)) {
    if (!e.isCharacter()) {
      table.drawArrowStoCenter(x, y);
    } else {
      table.drawCharacter(x, y, e.c);
      table.drawArrowStoEdge(x, y);
    }
  }

  if (e.hasClass(ElementClass::ArrowE)) {
    if (!e.isCharacter()) {
      table.drawArrowEtoCenter(x, y);
    } else {
      table.drawCharacter(x, y, e.c);
      table.drawArrowEtoEdge(x, y);
    }
  }

  if (e.hasClass(ElementClass::ArrowW)) {
    if (!e.isCharacter()) {
      table.drawArrowWtoCenter(x, y);
    } else {
      table.drawCharacter(x, y, e.c);
      table.drawArrowWtoEdge(x, y);
    }
  }
}
