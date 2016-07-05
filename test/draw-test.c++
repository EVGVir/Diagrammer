#include "draw.h++"

#include "drafting-table-mock.h++"
#include "test-utils.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;


struct DrawElementTest: public Test {
  StrictMock<DraftingTableMock> table;
  size_t x;
  size_t y;

  DrawElementTest():
    x{2}, y{3}
  {}
};


TEST_F(DrawElementTest, shouldDrawCharacterIfNoClasses) {
  DiagramElement e = {'e', {}};

  EXPECT_CALL(table, drawCharacter(x, y, e.c));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineN) {
  DiagramElement e = {'e', {ElementClass::LineN}};

  EXPECT_CALL(table, drawLineN(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineS) {
  DiagramElement e = {'e', {ElementClass::LineS}};

  EXPECT_CALL(table, drawLineS(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineE) {
  DiagramElement e = {'e', {ElementClass::LineE}};

  EXPECT_CALL(table, drawLineE(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineW) {
  DiagramElement e = {'e', {ElementClass::LineW}};

  EXPECT_CALL(table, drawLineW(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowN) {
  DiagramElement e = {'e', {ElementClass::ArrowN}};

  EXPECT_CALL(table, drawArrowN(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowS) {
  DiagramElement e = {'e', {ElementClass::ArrowS}};

  EXPECT_CALL(table, drawArrowS(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowE) {
  DiagramElement e = {'e', {ElementClass::ArrowE}};

  EXPECT_CALL(table, drawArrowE(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowW) {
  DiagramElement e = {'e', {ElementClass::ArrowW}};

  EXPECT_CALL(table, drawArrowW(x, y));
  drawElement(e, table, x, y);
}
