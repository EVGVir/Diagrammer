#include "draw.h++"
#include "patterns.h++"

#include "drafting-table-mock.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sstream>

using namespace testing;
using namespace std;


struct DrawDiagramTest: public Test {
  StrictMock<DraftingTableMock> table;
  stringstream ss;
};


TEST_F(DrawDiagramTest, shouldDrawHorizontalLine) {
  ss.str("--");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalLine) {
  ss.str("|\n"
         "|");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornerNE) {
  ss.str("| \n"
         "+-");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornerSE) {
  ss.str("+-\n"
         "| ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _));
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornerSW) {
  ss.str("-+\n"
         " |");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _));
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawLineE(_, _));
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornerNW) {
  ss.str(" |\n"
         "-+");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _));
  EXPECT_CALL(table, drawLineE(_, _));
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowN) {
  ss.str(" \n"
         "^\n"
         "|");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowN(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowS) {
  ss.str("|\n"
         "v\n"
         " ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowS(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowE) {
  ss.str("-> ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowE(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowW) {
  ss.str(" <-");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowW(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  drawDiagram(d, table);
}
