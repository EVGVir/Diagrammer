#pragma once

#include <docopt.h>
#include <string>


/// Command line options parser. (a wrapper around docopt.cpp)
class CommandLineOptions {
public:
  /// Constructor.
  ///
  /// @param argc The `argc` parameter passed to the main() function.
  /// @param argv The `argv` parameter passed to the main() function.
  CommandLineOptions(int argc, char *argv[]);

  /// @return Name of a file to read the diagram from.
  std::string inputFileName() const;

  /// @return Name of a file to write the diagram into.
  std::string outputFileName() const;

  /// @return If the debug is enabled.
  /// @retval true  The debug mode is enabled.
  /// @retval false The debug mode is disabled.
  bool isDebugMode() const;

private:
  /// The program 'usage' text.
  static const char mUsage[];

  /// Command line arguments (as returned by docopt).
  std::map<std::string, docopt::value> mArguments;
};
