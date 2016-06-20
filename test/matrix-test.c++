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
