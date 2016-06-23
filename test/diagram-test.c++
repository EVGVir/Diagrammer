#include "diagram.h++"
#include "test-utils.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sstream>

using namespace testing;
using namespace std;


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

  auto value = DiagramElement{0, ElementClasses{ElementClass::None}};

  value.c = 'a'; EXPECT_THAT(d[0][0], DiagramElementEq(value));
  value.c = 'b'; EXPECT_THAT(d[1][0], DiagramElementEq(value));
  value.c = 'c'; EXPECT_THAT(d[0][1], DiagramElementEq(value));
  value.c = 'd'; EXPECT_THAT(d[1][1], DiagramElementEq(value));
  value.c = 'e'; EXPECT_THAT(d[0][2], DiagramElementEq(value));
  value.c = 'f'; EXPECT_THAT(d[1][2], DiagramElementEq(value));
}
