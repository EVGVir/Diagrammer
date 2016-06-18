#include "gtest/gtest.h"
#include "ascii-matrix.h++"


using namespace testing;


TEST(AsciiMatrixTest, shouldReturn0_ifEmpty) {
  AsciiMatrix am;

  EXPECT_EQ(am.get(0, 0), 0);
  EXPECT_EQ(am.get(0, 1), 0);
  EXPECT_EQ(am.get(1, 0), 0);
  EXPECT_EQ(am.get(1, 1), 0);
}


TEST(AsciiMatrixTest, shouldAddString) {
  AsciiMatrix am;

  am << "abc";

  EXPECT_EQ(am.get(0, 0), 'a');
  EXPECT_EQ(am.get(1, 0), 'b');
  EXPECT_EQ(am.get(2, 0), 'c');
  EXPECT_EQ(am.get(3, 0), 0);
}


TEST(AsciiMatrixTest, shouldAddSeveralStrings) {
  AsciiMatrix am;

  am << "ab" << "c" << "dev";

  EXPECT_EQ(am.get(0, 0), 'a');
  EXPECT_EQ(am.get(1, 0), 'b');
  EXPECT_EQ(am.get(2, 0), 0);

  EXPECT_EQ(am.get(0, 1), 'c');
  EXPECT_EQ(am.get(1, 1), 0);

  EXPECT_EQ(am.get(0, 2), 'd');
  EXPECT_EQ(am.get(1, 2), 'e');
  EXPECT_EQ(am.get(2, 2), 'v');
  EXPECT_EQ(am.get(3, 2), 0);

  EXPECT_EQ(am.get(4, 0), 0);
  EXPECT_EQ(am.get(4, 4), 0);
}


TEST(AsciiMatrixTest, shouldAddEmptyString) {
  AsciiMatrix am;

  am << "a" << "" << "b";

  EXPECT_EQ(am.get(0, 0), 'a');
  EXPECT_EQ(am.get(1, 0), 0);

  EXPECT_EQ(am.get(0, 1), 0);

  EXPECT_EQ(am.get(0, 2), 'b');
  EXPECT_EQ(am.get(1, 2), 0);
}


TEST(AsciiMatrixTest, shouldConstructWithPattern) {
  unsigned char pattern[] = {
     0, 'a',
    'b', 0
  };

  AsciiMatrix am(2, 2, pattern);

  EXPECT_EQ(am.get(0, 0), 0);
  EXPECT_EQ(am.get(1, 0), 'a');

  EXPECT_EQ(am.get(0, 1), 'b');
  EXPECT_EQ(am.get(1, 1), 0);
}
