#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "matrix.h++"


using namespace testing;


struct MatrixTest: public Test {
  static const auto width{20};
  static const auto height{30};

  Matrix<int> m;

  MatrixTest():
    m{width, height}
  { }
};


TEST_F(MatrixTest, shouldGetZeroByDefault) {
  for (auto x = 0; x < width; ++x) {
    for (auto y = 0; y < height; ++y) {
      EXPECT_THAT(m[x][y], 0);
    }
  }
}


TEST_F(MatrixTest, shouldKeepElements) {
  for (auto x = 0; x < width; ++x) {
    for (auto y = 0; y < height; ++y) {
      m[x][y] = x * y;
    }
  }

  for (auto x = 0; x < width; ++x) {
    for (auto y = 0; y < height; ++y) {
      EXPECT_THAT(m[x][y], x * y);
    }
  }
}


TEST_F(MatrixTest, shouldReturnDimensions) {
  EXPECT_THAT(m.width(),  width);
  EXPECT_THAT(m.height(), height);
}


TEST_F(MatrixTest, shouldCopyMatrix) {
  for (auto x = 0; x < width; ++x) {
    for (auto y = 0; y < height; ++y) {
      m[x][y] = x * y;
    }
  }

  auto m2 = m;

  for (auto x = 0; x < width; ++x) {
    for (auto y = 0; y < height; ++y) {
      EXPECT_THAT(m2[x][y], m[x][y]);
    }
  }
}


TEST(MatrixTest_, shouldCreateWithInitializerList) {
  Matrix<int> m{{
      { 0,  2,  4},
      {-1, -3, -5}
  }};

  ASSERT_THAT(m.width(),  3);
  ASSERT_THAT(m.height(), 2);

  EXPECT_THAT(m[0][0],  0);
  EXPECT_THAT(m[1][0],  2);
  EXPECT_THAT(m[2][0],  4);
  EXPECT_THAT(m[0][1], -1);
  EXPECT_THAT(m[1][1], -3);
  EXPECT_THAT(m[2][1], -5);
}
