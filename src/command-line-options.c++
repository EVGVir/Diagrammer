#include "command-line-options.h++"
#include "utils.h++"

using std::string;


const char CommandLineOptions::mUsage[] =
R"(Diagrammer - ASCII diagrams to pictures converter.

Usage:
  diagrammer [options] <input-file>
  diagrammer --help

Options:
  --debug, -d                   Draw the diagram upon a grid.
  --font-size=<font-size>       Use the specified font size (in pixels).
                                [default: 14]
  --help                        Show this message and exit.
  --output=<file>, -o <file>    Place the output in the specified file.
                                [default: output.png]

Copyright Evgeny Gagauz, 2016.
)";


CommandLineOptions::CommandLineOptions(int argc, char *argv[]) {
  mArguments = docopt::docopt(mUsage, {argv + 1, argv + argc});
}


string CommandLineOptions::inputFileName() const {
  auto result = mArguments.find("<input-file>");
  ASSERT(result != mArguments.end(), "`<input-file>` is a mandatory argument, therefore it must contain a valid value.");
  return result->second.asString();
}


string CommandLineOptions::outputFileName() const {
  auto result = mArguments.find("--output");
  ASSERT(result != mArguments.end(), "`--output` has a default value, therefore it must contain a valid value.");
  return result->second.asString();
}


long CommandLineOptions::fontSize() const {
  auto result = mArguments.find("--font-size");
  ASSERT(result != mArguments.end(), "`--font-size` has a default value, therefore it must contain a valid value.");

  long font_size = 0;

  try {
    font_size = result->second.asLong();
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument{toString("Font size must be an integral value. Passed value: ", result->second.asString(), ".")};
  }

  if (font_size <= 0) {
    throw std::range_error{toString("Font size can't be less or equal 0. Passed value: ", font_size, ".")};
  }

  return font_size;
}


bool CommandLineOptions::isDebugMode() const {
  auto result = mArguments.find("--debug");
  ASSERT(result != mArguments.end(), "`--debug` is a boolean value, it must be false by default.");
  return result->second.asBool();
}
