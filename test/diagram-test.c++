#include "diagram.h++"
#include "patterns.h++"

#include "test-utils.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sstream>

using namespace testing;
using namespace std;


using EC = ElementClass;


struct DiagramTest: public Test {
  stringstream ss;

  DiagramTest():
    ss{"ab\ncd\nef\n"}
  { }
};


TEST_F(DiagramTest, shouldGetDimensions) {
  Diagram d{ss};

  EXPECT_THAT(d.width(), 2);
  EXPECT_THAT(d.height(), 3);
}


TEST_F(DiagramTest, shouldInitWithValues) {
  Diagram d{ss};

  auto value = DiagramElement{0, ElementClasses{EC::None}};

  value.c = 'a'; EXPECT_THAT(d[0][0], DiagramElementEq(value));
  value.c = 'b'; EXPECT_THAT(d[1][0], DiagramElementEq(value));
  value.c = 'c'; EXPECT_THAT(d[0][1], DiagramElementEq(value));
  value.c = 'd'; EXPECT_THAT(d[1][1], DiagramElementEq(value));
  value.c = 'e'; EXPECT_THAT(d[0][2], DiagramElementEq(value));
  value.c = 'f'; EXPECT_THAT(d[1][2], DiagramElementEq(value));
}


TEST_F(DiagramTest, shouldCheckPattern) {
  ss.str("  | \n"
         "--+ \n");
  Diagram d{ss};

  EXPECT_THAT(d.checkPattern(0, 1, Patterns::Lines::Horizontal), true);
  EXPECT_THAT(d.checkPattern(1, 0, Patterns::Corners::NW), true);
}


TEST_F(DiagramTest, shouldNotCheckPattern) {
  ss.str("  | \n"
         "--+ \n");
  Diagram d{ss};

  EXPECT_THAT(d.checkPattern(0, 0, Patterns::Lines::Horizontal), false);
  EXPECT_THAT(d.checkPattern(2, 0, Patterns::Corners::NW), false);
}


TEST_F(DiagramTest, shouldApplyPatternAtPos) {
  ss.str("|  \n"
         "|  \n"
         "+--\n");
  Diagram d{ss};

  d.applyPatternAtPos(0, 0, Patterns::Lines::Vertical);
  EXPECT_THAT(d[0][0].classes, UnorderedElementsAre(EC::None, EC::LineS, EC::LineN));
  EXPECT_THAT(d[0][1].classes, UnorderedElementsAre(EC::None, EC::LineS, EC::LineN));

  d.applyPatternAtPos(0, 1, Patterns::Corners::NE);
  EXPECT_THAT(d[0][1].classes, UnorderedElementsAre(EC::None, EC::LineS, EC::LineN));
  EXPECT_THAT(d[1][1].classes, ElementsAre(EC::None));
  EXPECT_THAT(d[0][2].classes, UnorderedElementsAre(EC::None, EC::LineN, EC::LineE));
  EXPECT_THAT(d[1][2].classes, UnorderedElementsAre(EC::None, EC::LineW, EC::LineE));

  EXPECT_THAT(d[1][0].classes, ElementsAre(EC::None));
  EXPECT_THAT(d[2][0].classes, ElementsAre(EC::None));
  EXPECT_THAT(d[2][1].classes, ElementsAre(EC::None));
  EXPECT_THAT(d[2][2].classes, ElementsAre(EC::None));
}
