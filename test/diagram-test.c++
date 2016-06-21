#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "diagram.h++"

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


TEST_F(DiagramTest, shouldGetValues) {
  Diagram d{ss};

  EXPECT_THAT(d[0][0], 'a');
  EXPECT_THAT(d[1][0], 'b');
  EXPECT_THAT(d[0][1], 'c');
  EXPECT_THAT(d[1][1], 'd');
  EXPECT_THAT(d[0][2], 'e');
  EXPECT_THAT(d[1][2], 'f');
}
