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
/// ^   .   . . >   < . .
/// .   v
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
/// ---   .         |   |        ^   < . . >
///  ^    v    . . >|   |< . .   .
///  .   ---        |   |        v
///
/// . . .   . .     .      .         .   .
///   ^      ^      v      v    . . >.   .< . .
///   .      .    . . .   . .        .   .
///
/// |     |   .     .   . . >+-        |    -+< . .    |
/// +-   -+   v     v        |    . . >+-    |        -+< . .
/// ^     ^   +-   -+
/// .     .   |     |
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowN) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowS) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowE) {
  ss.str("-> ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidArrowW) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowNtoHorizontalSolidLine) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowStoHorizontalSolidLine) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowEtoVerticalSolidLine) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowWtoVerticalSolidLine) {
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


TEST_F(DrawDiagramTest, shouldDrawDoubleSidedVerticalSolidArrow) {
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


TEST_F(DrawDiagramTest, shouldDrawDoubleSidedHorizontalSolidArrow) {
  ss.str(" <-> ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidArrowNtoSolidCornerNE) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowNtoSolidCornerNW) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowStoSolidCornerSE) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowStoSolidCornerSW) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowEtoSolidCornerSE) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowEtoSolidCornerNE) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowWtoSolidCornerSW) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowWtoSolidCornerNW) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowNtoCharacter) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowStoCharacter) {
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


TEST_F(DrawDiagramTest, shouldDrawSolidArrowEtoCharacter) {
  ss.str("->a");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawCharacter(_, _, 'a'));
  EXPECT_CALL(table, drawArrowEtoEdge(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawSolidArrowWtoCharacter) {
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


TEST_F(DrawDiagramTest, shouldDrawDashedArrowN) {
  ss.str(" \n"
         "^\n"
         ".");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(1);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowS) {
  ss.str(".\n"
         "v\n"
         " ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(1);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowE) {
  ss.str(". . > ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(5);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowW) {
  ss.str(" < . .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(5);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowNtoHorizontalSolidLine) {
  ss.str("---\n"
         " ^ \n"
         " . ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(1);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowStoHorizontalSolidLine) {
  ss.str(" . \n"
         " v \n"
         "---");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(3);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(1);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowEtoVerticalSolidLine) {
  ss.str("     |\n"
         ". . >|\n"
         "     |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(5);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(10);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowWtoVerticalSolidLine) {
  ss.str("|     \n"
         "|< . .\n"
         "|     ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(5);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(3);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(10);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDoubleSidedVerticalDashedArrow) {
  ss.str(" \n"
         "^\n"
         ".\n"
         "v\n"
         " ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(3);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDoubleSidedHorizontalDashedArrow) {
  ss.str(" < . . > ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(7);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(7);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowNtoHorizontalDashedLine) {
  ss.str(". . .\n"
         "  ^  \n"
         "  .  ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(1);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(8);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowNtoHorizontalDashedLineToSpace) {
  ss.str(". .\n"
         " ^ \n"
         " . ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(1);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowStoHorizontalDashedLine) {
  ss.str("  .  \n"
         "  v  \n"
         ". . .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(1);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(8);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowStoHorizontalDashedLineToSpace) {
  ss.str(" . \n"
         " v \n"
         ". .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(1);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(4);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowEtoVerticalDashedLine) {
  ss.str("     .\n"
         ". . >.\n"
         "     .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(5);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(10);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowWtoVerticalDashedLine) {
  ss.str(".     \n"
         ".< . .\n"
         ".     ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(5);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(10);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowNtoSolidCornerNE) {
  ss.str("| \n"
         "+-\n"
         "^ \n"
         ". ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowNtoSolidCornerNW) {
  ss.str(" |\n"
         "-+\n"
         " ^\n"
         " .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawArrowNtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowStoSolidCornerSE) {
  ss.str(". \n"
         "v \n"
         "+-\n"
         "| ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawDashedLineN(_, _));
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowStoSolidCornerSW) {
  ss.str(" .\n"
         " v\n"
         "-+\n"
         " |");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowStoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawDashedLineN(_, _));
  EXPECT_CALL(table, drawDashedLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(3);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowEtoSolidCornerSE) {
  ss.str(". . >+-\n"
         "     | ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(5);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(6);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowEtoSolidCornerNE) {
  ss.str("     | \n"
         ". . >+-");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(5);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(4);
  EXPECT_CALL(table, drawSolidLineE(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineW(_, _));
  EXPECT_CALL(table, drawArrowEtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(6);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowWtoSolidCornerSW) {
  ss.str("-+< . .\n"
         " |     ");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(5);
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _));
  EXPECT_CALL(table, drawSolidLineS(_, _)).Times(2);
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(6);
  drawDiagram(d, table);
}


TEST_F(DrawDiagramTest, shouldDrawDashedArrowWtoSolidCornerNW) {
  ss.str(" |     \n"
         "-+< . .");
  Diagram d{ss};
  applyAllPatterns(d);

  EXPECT_CALL(table, drawDashedLineE(_, _)).Times(4);
  EXPECT_CALL(table, drawDashedLineW(_, _)).Times(5);
  EXPECT_CALL(table, drawSolidLineE(_, _));
  EXPECT_CALL(table, drawSolidLineW(_, _)).Times(2);
  EXPECT_CALL(table, drawArrowWtoCenter(_, _));
  EXPECT_CALL(table, drawSolidLineN(_, _)).Times(2);
  EXPECT_CALL(table, drawSolidLineS(_, _));
  EXPECT_CALL(table, drawCharacter(_, _, ' ')).Times(6);
  drawDiagram(d, table);
}
