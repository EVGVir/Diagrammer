#include "command-line-options.h++"
#include "test-utils.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <exception>
#include <vector>

using namespace testing;
using std::vector;


/// Transfers a list of C-strings (by converting this list into `argc`
/// and `argv` arguments) to CommandLineOptions constructor.
CommandLineOptions getOptions(vector<const char *> args) {
  CommandLineOptions options{(int)args.size(), (char **)args.data()};
  return options;
}


TEST(CommandLineOptionsTest, shouldNotAcceptNoArguments) {
  FLAGS_gtest_death_test_style = "threadsafe";
  EXPECT_DEATH(getOptions({"diagrammer"}), "Arguments did not match expected patterns");
}


TEST(CommandLineOptionsTest, shouldAcceptInputFile) {
  auto options = getOptions({"diagrammer", "diagram"});
  EXPECT_THAT(options.inputFileName(), "diagram");
  EXPECT_THAT(options.outputFileName(), "output.png");
  EXPECT_THAT(options.isDebugMode(), false);
  EXPECT_THAT(options.fontSize(), 14);
}


TEST(CommandLineOptionsTest, shouldNotAcceptTwoInputFiles) {
  FLAGS_gtest_death_test_style = "threadsafe";
  EXPECT_DEATH(getOptions({"diagrammer", "diagram1", "diagram2"}), "diagram1.+diagram2");
}


TEST(CommandLineOptionsTest, shouldEnableDebugMode_Long) {
  auto options = getOptions({"diagrammer", "diagram", "--debug"});
  EXPECT_THAT(options.inputFileName(), "diagram");
  EXPECT_THAT(options.outputFileName(), "output.png");
  EXPECT_THAT(options.isDebugMode(), true);
}


TEST(CommandLineOptionsTest, shouldEnableDebugMode_Short) {
  auto options = getOptions({"diagrammer", "diagram", "-d"});
  EXPECT_THAT(options.inputFileName(), "diagram");
  EXPECT_THAT(options.outputFileName(), "output.png");
  EXPECT_THAT(options.isDebugMode(), true);
}


TEST(CommandLineOptionsTest, shouldChangeOutputFile_LongWithSpace) {
  auto options = getOptions({"diagrammer", "diagram", "--output", "long.png"});
  EXPECT_THAT(options.inputFileName(), "diagram");
  EXPECT_THAT(options.outputFileName(), "long.png");
  EXPECT_THAT(options.isDebugMode(), false);
}


TEST(CommandLineOptionsTest, shouldChangeOutputFile_LongWithEqual) {
  auto options = getOptions({"diagrammer", "diagram", "--output=long.png"});
  EXPECT_THAT(options.inputFileName(), "diagram");
  EXPECT_THAT(options.outputFileName(), "long.png");
  EXPECT_THAT(options.isDebugMode(), false);
}


TEST(CommandLineOptionsTest, shouldChangeOutputFile_ShortWithoutSpace) {
  auto options = getOptions({"diagrammer", "diagram", "-oshort.png"});
  EXPECT_THAT(options.inputFileName(), "diagram");
  EXPECT_THAT(options.outputFileName(), "short.png");
  EXPECT_THAT(options.isDebugMode(), false);
}


TEST(CommandLineOptionsTest, shouldChangeOutputFile_ShortWithSpace) {
  auto options = getOptions({"diagrammer", "diagram", "-o", "short.png"});
  EXPECT_THAT(options.inputFileName(), "diagram");
  EXPECT_THAT(options.outputFileName(), "short.png");
  EXPECT_THAT(options.isDebugMode(), false);
}


TEST(CommandLineOptionsTest, shouldChangeFontSize_LongWithSpace) {
  auto options = getOptions({"diagrammer", "diagram", "--font-size", "5"});
  EXPECT_THAT(options.fontSize(), 5);
}


TEST(CommandLineOptionsTest, shouldChangeFontSize_LongWithEqual) {
  auto options = getOptions({"diagrammer", "diagram", "--font-size=15"});
  EXPECT_THAT(options.fontSize(), 15);
}


TEST(CommandLineOptionsTest, shouldNotAcceptZeroFontSize) {
  auto options = getOptions({"diagrammer", "diagram", "--font-size", "0"});
  EXPECT_THROW_WHATEQ(options.fontSize(), std::range_error,
                      "Font size can't be less or equal 0. Passed value: 0.");
}


TEST(CommandLineOptionsTest, shouldNotAcceptNegativeFontSize) {
  auto options = getOptions({"diagrammer", "diagram", "--font-size", "-3"});
  EXPECT_THROW_WHATEQ(options.fontSize(), std::range_error,
                      "Font size can't be less or equal 0. Passed value: -3.");
}


TEST(CommandLineOptionsTest, shouldNotAcceptNaNFontSize) {
  auto options = getOptions({"diagrammer", "diagram", "--font-size", "NaN"});
  EXPECT_THROW_WHATEQ(options.fontSize(), std::invalid_argument,
                      "Font size must be an integral value. Passed value: NaN.");
}
