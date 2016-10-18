#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "utils.h++"


using namespace testing;


TEST(UtilsTest, shouldConvertIntToString) {
  EXPECT_THAT(toString(5), std::string("5"));
}


TEST(UtilsTest, shouldConvertOctIntToString) {
  EXPECT_THAT(toString(0123), std::string("83"));
}


TEST(UtilsTest, shouldConvertHexIntToString) {
  EXPECT_THAT(toString(0xbeaf), std::string("48815"));
}


TEST(UtilsTest, shouldConvertFloatToString) {
  EXPECT_THAT(toString(3.14), std::string("3.14"));
}


TEST(UtilsTest, shouldConvertFloatToString_withExp) {
  EXPECT_THAT(toString(0.00001), std::string("1e-05"));
}


TEST(UtilsTest, shouldConvertCStringToString) {
  EXPECT_THAT(toString("abc"), std::string("abc"));
}


TEST(UtilsTest, shouldConvertPointerToString) {
  EXPECT_THAT(toString((void *)0xbeaf), std::string("0xbeaf"));
}
