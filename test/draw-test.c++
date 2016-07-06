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
  DiagramElement e{'e'};

  EXPECT_CALL(table, drawCharacter(x, y, e.c));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineN) {
  DiagramElement e{'e', {ElementClass::LineN}};

  EXPECT_CALL(table, drawLineN(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineS) {
  DiagramElement e{'e', {ElementClass::LineS}};

  EXPECT_CALL(table, drawLineS(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineE) {
  DiagramElement e{'e', {ElementClass::LineE}};

  EXPECT_CALL(table, drawLineE(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawLineW) {
  DiagramElement e{'e', {ElementClass::LineW}};

  EXPECT_CALL(table, drawLineW(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowNtoCenter) {
  DiagramElement e{' ', {ElementClass::ArrowN}};

  EXPECT_CALL(table, drawArrowNtoCenter(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowStoCenter) {
  DiagramElement e{' ', {ElementClass::ArrowS}};

  EXPECT_CALL(table, drawArrowStoCenter(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowEtoCenter) {
  DiagramElement e{' ', {ElementClass::ArrowE}};

  EXPECT_CALL(table, drawArrowEtoCenter(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowWtoCenter) {
  DiagramElement e{' ', {ElementClass::ArrowW}};

  EXPECT_CALL(table, drawArrowWtoCenter(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowNtoCharacter) {
  DiagramElement e{'e', {ElementClass::ArrowN}};

  EXPECT_CALL(table, drawCharacter(x, y, e.c));
  EXPECT_CALL(table, drawArrowNtoEdge(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowStoCharacter) {
  DiagramElement e{'e', {ElementClass::ArrowS}};

  EXPECT_CALL(table, drawCharacter(x, y, e.c));
  EXPECT_CALL(table, drawArrowStoEdge(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowEtoCharacter) {
  DiagramElement e{'e', {ElementClass::ArrowE}};

  EXPECT_CALL(table, drawCharacter(x, y, e.c));
  EXPECT_CALL(table, drawArrowEtoEdge(x, y));
  drawElement(e, table, x, y);
}


TEST_F(DrawElementTest, shouldDrawArrowWtoCharacter) {
  DiagramElement e{'e', {ElementClass::ArrowW}};

  EXPECT_CALL(table, drawCharacter(x, y, e.c));
  EXPECT_CALL(table, drawArrowWtoEdge(x, y));
  drawElement(e, table, x, y);
}
