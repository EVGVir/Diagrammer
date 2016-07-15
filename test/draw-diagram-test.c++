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
/// . .   .
///       .
///
/// .     . .   . .     .
/// . .   .       .   . .
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
/// ---    .        |   |          |   |
///  .     .    . . |   | . .   . .|   |. .
///  .    ---       |   |          |   |
///
/// |     |   .     .   . . +-   . .+-       |       |    -+ . .   -+. .    |        |
/// +-   -+   .     .       |       |    . . +-   . .+-    |        |      -+ . .   -+. .
/// .     .   +-   -+
/// .     .   |     |
///
/// . . .   . .     |      |      .   .
///   |      |      |      |    --.   .--
///   |      |    . . .   . .     .   .
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


TEST_F(DrawDiagramTest, shouldDrawHorizontalSolidLine) {
  ss.str("--");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalSolidLine) {
  ss.str("|\n"
         "|");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNE) {
  ss.str("| \n"
         "+-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSE) {
  ss.str("+-\n"
         "| ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSW) {
  ss.str("-+\n"
         " |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNW) {
  ss.str(" |\n"
         "-+");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' '));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowN) {
  ss.str(" \n"
         "^\n"
         "|");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowS) {
  ss.str("|\n"
         "v\n"
         " ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowE) {
  ss.str("-> ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowW) {
  ss.str(" <-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawHorizontalDashedLine) {
  ss.str(". .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalDashedLine) {
  ss.str(".\n"
         ".");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineN(_, _));
  EXPECT_CALL(table, drawDashedLineS(_, _));
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedCornerNE) {
  ss.str(".  \n"
         ". .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineN(_, _));
  EXPECT_CALL(table, drawDashedLineS(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedCornerSE) {
  ss.str(". .\n"
         ". ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineN(_, _));
  EXPECT_CALL(table, drawDashedLineS(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedCornerSW) {
  ss.str(". .\n"
         "  .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineN(_, _));
  EXPECT_CALL(table, drawDashedLineS(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedCornerNW) {
  ss.str("  .\n"
         ". .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineN(_, _));
  EXPECT_CALL(table, drawDashedLineS(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornersNEandSE) {
  ss.str("| \n"
         "+-\n"
         "| ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornersNWandSW) {
  ss.str(" |\n"
         "-+\n"
         " |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornersNEandNW) {
  ss.str(" | \n"
         "-+-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornersSEandSW) {
  ss.str("-+-\n"
         " | ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoHorizontalSolidLine) {
  ss.str("--\n"
         "^ \n"
         "| ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoHorizontalSolidLine) {
  ss.str("| \n"
         "v \n"
         "--");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoVerticalSolidLine) {
  ss.str("->|\n"
         "  |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoVerticalSolidLine) {
  ss.str("|<-\n"
         "|  ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
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
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDoubleSidedHorizontalArrow) {
  ss.str(" <-> ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoSolidCornerNE) {
  ss.str("| \n"
         "+-\n"
         "^ \n"
         "| ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoSolidCornerNW) {
  ss.str(" |\n"
         "-+\n"
         " ^\n"
         " |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoSolidCornerSE) {
  ss.str("| \n"
         "v \n"
         "+-\n"
         "| ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoSolidCornerSW) {
  ss.str(" |\n"
         " v\n"
         "-+\n"
         " |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoSolidCornerSE) {
  ss.str("->+-\n"
         "  | ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoSolidCornerNE) {
  ss.str("  | \n"
         "->+-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoSolidCornerSW) {
  ss.str("-+<-\n"
         " |  ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoSolidCornerNW) {
  ss.str(" |  \n"
         "-+<-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowNtoCharacter) {
  ss.str("a\n"
         "^\n"
         "|");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowNtoEdge(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowStoCharacter) {
  ss.str("|\n"
         "v\n"
         "a");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowStoEdge(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowEtoCharacter) {
  ss.str("->a");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowEtoEdge(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawArrowWtoCharacter) {
  ss.str("a<-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowWtoEdge(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidLinesCross) {
  ss.str(" | \n"
         "-+-\n"
         " | ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalDashedLineFromSToHorizontalSolidLine) {
  ss.str("---\n"
         " . \n"
         " . ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalDashedLineFromNToHorizontalSolidLine) {
  ss.str(" . \n"
         " . \n"
         "---");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawHorizontalDashedLineFromWToVerticalSolidLine) {
  ss.str("    |\n"
         ". . |\n"
         "    |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(8);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawHorizontalDashedLineFromEToVerticalSolidLine) {
  ss.str("|    \n"
         "| . .\n"
         "|    ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(8);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawHorizontalDashedLineFromWToVerticalSolidLineWithoutSpace) {
  ss.str("   |\n"
         ". .|\n"
         "   |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(6);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawHorizontalDashedLineFromEToVerticalSolidLineWithoutSpace) {
  ss.str("|   \n"
         "|. .\n"
         "|   ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(6);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNEandVerticalDashedLine) {
  ss.str("| \n"
         "+-\n"
         ". \n"
         ". ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNWandVerticalDashedLine) {
  ss.str(" |\n"
         "-+\n"
         " .\n"
         " .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSEandVerticalDashedLine) {
  ss.str(". \n"
         ". \n"
         "+-\n"
         "| ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSWandVerticalDashedLine) {
  ss.str(" .\n"
         " .\n"
         "-+\n"
         " |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSEandHorizontalDashedLine) {
  ss.str(". . +-\n"
         "    | ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(5);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSEandHorizontalDashedLineWithoutSpace) {
  ss.str(". .+-\n"
         "   | ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNEandHorizontalDashedLine) {
  ss.str("    | \n"
         ". . +-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(5);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNEandHorizontalDashedLineWithoutSpace) {
  ss.str("   | \n"
         ". .+-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSWandHorizontalDashedLine) {
  ss.str("-+ . .\n"
         " |    ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(5);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerSWandHorizontalDashedLineWithoutSpace) {
  ss.str("-+. .\n"
         " |   ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNWandHorizontalDashedLine) {
  ss.str(" |    \n"
         "-+ . .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(5);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidCornerNWandHorizontalDashedLineWithoutSpace) {
  ss.str(" |   \n"
         "-+. .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalSolidLineFromSToHorizontalDashedLine) {
  ss.str(". . .\n"
         "  |  \n"
         "  |  ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(8);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalSolidLineFromSToHorizontalDashedLineToSpace) {
  ss.str(". .\n"
         " | \n"
         " | ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalSolidLineFromNToHorizontalDashedLine) {
  ss.str("  |  \n"
         "  |  \n"
         ". . .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(8);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawVerticalSolidLineFromNToHorizontalDashedLineToSpace) {
  ss.str(" | \n"
         " | \n"
         ". .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawHorizontalSolidLineFromWToVerticalDashedLine) {
  ss.str("  .\n"
         "--.\n"
         "  .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawHorizontalSolidLineFromEToVerticalDashedLine) {
  ss.str(".  \n"
         ".--\n"
         ".  ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}
