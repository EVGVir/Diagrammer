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

  const Pattern HorizontalLine{{
    {{'-', {EC::SolidLineW, EC::SolidLineE}}, {'-', {EC::SolidLineW, EC::SolidLineE}}}
  }};

  const Pattern VerticalLine{{
    {{'|', {EC::SolidLineS, EC::SolidLineN}}},
    {{'|', {EC::SolidLineS, EC::SolidLineN}}}
  }};

  const Pattern CornerNW{{
    {{ 0 , {}},                               {'|', {EC::SolidLineS, EC::SolidLineN}}},
    {{'-', {EC::SolidLineW, EC::SolidLineE}}, {'+', {EC::SolidLineN, EC::SolidLineW}}}
  }};

  const Pattern CornerNE{{
    {{'|', {EC::SolidLineS, EC::SolidLineN}}, { 0 , {}}},
    {{'+', {EC::SolidLineN, EC::SolidLineE}}, {'-', {EC::SolidLineW, EC::SolidLineE}}}
  }};


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

  DiagramElement value;

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

  EXPECT_THAT(d.checkPattern(0, 1, HorizontalLine), true);
  EXPECT_THAT(d.checkPattern(1, 0, CornerNW), true);
}


TEST_F(DiagramTest, shouldNotCheckPattern) {
  ss.str("  | \n"
         "--+ \n");
  Diagram d{ss};

  EXPECT_THAT(d.checkPattern(0, 0, HorizontalLine), false);
  EXPECT_THAT(d.checkPattern(2, 0, CornerNW), false);
}


TEST_F(DiagramTest, shouldApplyPatternAtPos) {
  ss.str("|  \n"
         "|  \n"
         "+--\n");
  Diagram d{ss};

  d.applyPatternAtPos(0, 0, VerticalLine);
  EXPECT_THAT(d[0][0].classes, UnorderedElementsAre(EC::SolidLineS, EC::SolidLineN));
  EXPECT_THAT(d[0][1].classes, UnorderedElementsAre(EC::SolidLineS, EC::SolidLineN));

  d.applyPatternAtPos(0, 1, CornerNE);
  EXPECT_THAT(d[0][1].classes, UnorderedElementsAre(EC::SolidLineS, EC::SolidLineN));
  EXPECT_THAT(d[1][1].classes, ElementsAre());
  EXPECT_THAT(d[0][2].classes, UnorderedElementsAre(EC::SolidLineN, EC::SolidLineE));
  EXPECT_THAT(d[1][2].classes, UnorderedElementsAre(EC::SolidLineW, EC::SolidLineE));

  EXPECT_THAT(d[1][0].classes, ElementsAre());
  EXPECT_THAT(d[2][0].classes, ElementsAre());
  EXPECT_THAT(d[2][1].classes, ElementsAre());
  EXPECT_THAT(d[2][2].classes, ElementsAre());
}


TEST_F(DiagramTest, shouldApplyPattern) {
  ss.str("+--+\n"
         "--  \n");
  Diagram d{ss};

  d.applyPattern(HorizontalLine);
  EXPECT_THAT(d[0][0].classes, UnorderedElementsAre());
  EXPECT_THAT(d[1][0].classes, UnorderedElementsAre(EC::SolidLineE, EC::SolidLineW));
  EXPECT_THAT(d[2][0].classes, UnorderedElementsAre(EC::SolidLineE, EC::SolidLineW));
  EXPECT_THAT(d[3][0].classes, UnorderedElementsAre());
  EXPECT_THAT(d[0][1].classes, UnorderedElementsAre(EC::SolidLineE, EC::SolidLineW));
  EXPECT_THAT(d[1][1].classes, UnorderedElementsAre(EC::SolidLineE, EC::SolidLineW));
  EXPECT_THAT(d[2][1].classes, UnorderedElementsAre());
  EXPECT_THAT(d[3][1].classes, UnorderedElementsAre());
}


TEST_F(DiagramTest, shouldNotApplyPattern) {
  ss.str("+-+\n"
         "| |\n"
         "+- \n");
  Diagram d{ss};

  d.applyPattern(CornerNW);
  for (size_t x = 0; x < d.width(); ++x) {
    for (size_t y = 0; y < d.height(); ++y) {
      EXPECT_THAT(d[x][y].classes, UnorderedElementsAre());
    }
  }
}
