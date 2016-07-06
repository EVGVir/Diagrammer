#include "draw.h++"
#include "patterns.h++"

#include "drafting-table-mock.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sstream>

using namespace testing;
using namespace std;


/// Tests in this file covers following cases.
///
/// One element
/// -----------
///
/// --   |   ^   |   ->   <-
///      |   |   v
///
/// |    +-   -+    |
/// +-   |     |   -+
///
///
/// Two elements
/// ------------
///
/// |     |    |    -+-
/// +-   -+   -+-    |
/// |     |
///
/// --   |    ->|   |<-   ^   <->
/// ^    v      |   |     |
/// |    --               v
///
/// |     |   |     |   ->+-     |    -+<-    |
/// +-   -+   v     v     |    ->+-    |     -+<-
/// ^     ^   +-   -+
/// |     |   |     |
///
/// a   |   ->a   a<-
/// ^   v
/// |   a
///
///
/// Other
/// -----
///
///  |
/// -+-
///  |


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

  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
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

  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowE) {
  ss.str("-> ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowW) {
  ss.str(" <-");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornersNEandSE) {
  ss.str("| \n"
         "+-\n"
         "| ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornersNWandSW) {
  ss.str(" |\n"
         "-+\n"
         " |");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawLineE(_, _));
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornersNEandNW) {
  ss.str(" | \n"
         "-+-");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawCornersSEandSW) {
  ss.str("-+-\n"
         " | ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _));
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoHorizontalLine) {
  ss.str("--\n"
         "^ \n"
         "| ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoHorizontalLine) {
  ss.str("| \n"
         "v \n"
         "--");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoVerticalLine) {
  ss.str("->|\n"
         "  |");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoVerticalLine) {
  ss.str("|<-\n"
         "|  ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDoubleSidedVerticalArrow) {
  ss.str(" \n"
         "^\n"
         "|\n"
         "v\n"
         " ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawLineS(_, _)).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDoubleSidedHorizontalArrow) {
  ss.str(" <-> ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawLineW(_, _)).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoCornerNE) {
  ss.str("| \n"
         "+-\n"
         "^ \n"
         "| ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(4);
  EXPECT_CALL(table, drawLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoCornerNW) {
  ss.str(" |\n"
         "-+\n"
         " ^\n"
         " |");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(4);
  EXPECT_CALL(table, drawLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _));
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoCornerSE) {
  ss.str("| \n"
         "v \n"
         "+-\n"
         "| ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawLineS(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoCornerSW) {
  ss.str(" |\n"
         " v\n"
         "-+\n"
         " |");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawLineS(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawLineE(_, _));
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoCornerSE) {
  ss.str("->+-\n"
         "  | ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _));
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoCornerNE) {
  ss.str("  | \n"
         "->+-");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoCornerSW) {
  ss.str("-+<-\n"
         " |  ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _));
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoCornerNW) {
  ss.str(" |  \n"
         "-+<-");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoCharacter) {
  ss.str("a\n"
         "^\n"
         "|");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowNtoEdge(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoCharacter) {
  ss.str("|\n"
         "v\n"
         "a");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowStoEdge(_, _));
  EXPECT_CALL(table, drawLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoCharacter) {
  ss.str("->a");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowEtoEdge(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoCharacter) {
  ss.str("a<-");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowWtoEdge(_, _));
  EXPECT_CALL(table, drawLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawLinesCross) {
  ss.str(" | \n"
         "-+-\n"
         " | ");
  Diagram d{ss};
  Patterns::applyAll(d);

  EXPECT_CALL(table, drawLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}
