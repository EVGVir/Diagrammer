#include "command-line-options.h++"
#include "utils.h++"

using std::string;


const char CommandLineOptions::mUsage[] =
R"(Diagrammer - ASCII diagrams to pictures converter.

Usage:
  diagrammer [--debug] [--output=<file>] <input-file>
  diagrammer --help

Options:
  --debug, -d                   Draw the diagram upon a grid.
  --help                        Show this message and exit.
  --output=<file>, -o <file>    Place the output in the specified file. [default: output.png]

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


bool CommandLineOptions::isDebugMode() const {
  auto result = mArguments.find("--debug");
  ASSERT(result != mArguments.end(), "`--debug` is a boolean value, it must be false by default.");
  return result->second.asBool();
}
