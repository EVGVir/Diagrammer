#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ascii-matrix.h++"


using namespace testing;


const unsigned char patternT[] = {
  '-', '+', '-',
   0 , '|',  0
};


TEST(AsciiMatrixTest, shouldReturn0_ifEmpty) {
  AsciiMatrix am;

  EXPECT_THAT(am.get(0, 0), 0);
  EXPECT_THAT(am.get(0, 1), 0);
  EXPECT_THAT(am.get(1, 0), 0);
  EXPECT_THAT(am.get(1, 1), 0);
}


TEST(AsciiMatrixTest, shouldAddString) {
  AsciiMatrix am;

  am << "abc";

  EXPECT_THAT(am.get(0, 0), 'a');
  EXPECT_THAT(am.get(1, 0), 'b');
  EXPECT_THAT(am.get(2, 0), 'c');
  EXPECT_THAT(am.get(3, 0),  0 );
}


TEST(AsciiMatrixTest, shouldAddSeveralStrings) {
  AsciiMatrix am;

  am << "ab" << "c" << "dev";

  EXPECT_THAT(am.get(0, 0), 'a');
  EXPECT_THAT(am.get(1, 0), 'b');
  EXPECT_THAT(am.get(2, 0),  0 );

  EXPECT_THAT(am.get(0, 1), 'c');
  EXPECT_THAT(am.get(1, 1),  0 );

  EXPECT_THAT(am.get(0, 2), 'd');
  EXPECT_THAT(am.get(1, 2), 'e');
  EXPECT_THAT(am.get(2, 2), 'v');
  EXPECT_THAT(am.get(3, 2),  0 );

  EXPECT_THAT(am.get(4, 0),  0 );
  EXPECT_THAT(am.get(4, 4),  0 );
}


TEST(AsciiMatrixTest, shouldAddEmptyString) {
  AsciiMatrix am;

  am << "a" << "" << "b";

  EXPECT_THAT(am.get(0, 0), 'a');
  EXPECT_THAT(am.get(1, 0),  0 );

  EXPECT_THAT(am.get(0, 1),  0 );

  EXPECT_THAT(am.get(0, 2), 'b');
  EXPECT_THAT(am.get(1, 2),  0 );
}


TEST(AsciiMatrixTest, shouldConstructWithPattern) {
  unsigned char pattern[] = {
     0, 'a',
    'b', 0
  };

  AsciiMatrix am(2, 2, pattern);

  EXPECT_THAT(am.get(0, 0),  0 );
  EXPECT_THAT(am.get(1, 0), 'a');

  EXPECT_THAT(am.get(0, 1), 'b');
  EXPECT_THAT(am.get(1, 1),  0 );
}


TEST(AsciiMatrixTest, shouldGetWidth) {
  AsciiMatrix empty;
  EXPECT_THAT(empty.width(), 0);

  unsigned char pattern[] = {
    0, 'a', 0
  };

  AsciiMatrix am(3, 1, pattern);
  EXPECT_THAT(am.width(), 3);

  am << "12";
  EXPECT_THAT(am.width(), 3);

  am << "123";
  EXPECT_THAT(am.width(), 3);

  am << "1234";
  EXPECT_THAT(am.width(), 4);

  am << "1";
  EXPECT_THAT(am.width(), 4);
}


TEST(AsciiMatrixTest, shouldGetHeight) {
  AsciiMatrix empty;
  EXPECT_THAT(empty.height(), 0);

  unsigned char pattern[] = {
    0, 'a', 0
  };

  AsciiMatrix am(3, 1, pattern);
  EXPECT_THAT(am.height(), 1);

  am << "a";
  EXPECT_THAT(am.height(), 2);
}


TEST(AsciiMatrixTest, shouldFindSimplePattern) {
  AsciiMatrix p(3, 2, patternT);
  AsciiMatrix am;

  am << "     ";
  am << " -+- ";
  am << "  |  ";
  am << "     ";

  std::vector<TPoint> points = am.findPattern(p);
  ASSERT_THAT(points.size(), 1);
  EXPECT_THAT(points[0].x, 1);
  EXPECT_THAT(points[0].y, 1);
}


TEST(AsciiMatrixTest, shouldNotFindPattern) {
  AsciiMatrix p(3, 2, patternT);
  AsciiMatrix am;

  am << "     ";
  am << " --- ";
  am << "  |  ";
  am << "     ";

  std::vector<TPoint> points = am.findPattern(p);
  EXPECT_THAT(points.size(), 0);
}


TEST(AsciiMatrixTest, shouldFindSeveralPatterns) {
  AsciiMatrix p(3, 2, patternT);
  AsciiMatrix am;

  am << "-+-   ";
  am << " | -+-";
  am << "    | ";

  std::vector<TPoint> points = am.findPattern(p);
  ASSERT_THAT(points.size(), 2);
  EXPECT_THAT(points[0].x, 0);
  EXPECT_THAT(points[0].y, 0);
  EXPECT_THAT(points[1].x, 3);
  EXPECT_THAT(points[1].y, 1);
}


TEST(AsciiMatrixTest, shouldFindPatternsOverlappedByCharacter) {
  AsciiMatrix p(3, 2, patternT);
  AsciiMatrix am;

  am << "-+-+-";
  am << " | | ";

  std::vector<TPoint> points = am.findPattern(p);
  ASSERT_THAT(points.size(), 2);
  EXPECT_THAT(points[0].x, 0);
  EXPECT_THAT(points[0].y, 0);
  EXPECT_THAT(points[1].x, 2);
  EXPECT_THAT(points[1].y, 0);
}


TEST(AsciiMatrixTest, shouldFindPatternsOverlappedByEmptySpace) {
  AsciiMatrix p(3, 2, patternT);
  AsciiMatrix am;

  am << "-+-  ";
  am << " |-+-";
  am << "   | ";

  std::vector<TPoint> points = am.findPattern(p);
  ASSERT_THAT(points.size(), 2);
  EXPECT_THAT(points[0].x, 0);
  EXPECT_THAT(points[0].y, 0);
  EXPECT_THAT(points[1].x, 2);
  EXPECT_THAT(points[1].y, 1);
}


TEST(AsciiMatrixTest, shouldNotFindPatternInNarrowPicture) {
  AsciiMatrix p(3, 2, patternT);
  AsciiMatrix am;

  am << "-+";
  am << " |";

  ASSERT_THAT(am.findPattern(p).size(), 0);
}


TEST(AsciiMatrixTest, shouldNotFindPatternInShortPicture) {
  AsciiMatrix p(3, 2, patternT);
  AsciiMatrix am;

  am << "-+-";

  ASSERT_THAT(am.findPattern(p).size(), 0);
}
