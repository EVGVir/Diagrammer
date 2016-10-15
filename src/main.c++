#include "command-line-options.h++"
#include "diagram.h++"
#include "drafting-table.h++"
#include "draw.h++"
#include "patterns.h++"
#include "utils.h++"

#include <iostream>
#include <fstream>
#include <string>


/// Saves a diagram into a PNG file.
///
/// @note All patterns are applied to the diagram, prio to its
/// rasterizing.
///
/// @param d Diagram to be saved.
/// @param filename File, the diagram to be saved to.
/// @param fontsize Font size that is used for rasterization.
/// @param isDebugMode Shows if debug information must be drawn:
///   - true  - the debug information must be drawn.
///   - false - the debug information must not be drawn;
void diagram2png(Diagram &d, const std::string &filename, double fontsize, bool isDebugMode) {
  applyAllPatterns(d);
  auto table = DraftingTable{d.width(), d.height(), fontsize};
  if (isDebugMode) {
    table.drawMesh();
  }
  drawDiagram(d, table);
  table.saveToPNG(filename);
}


int main(int argc, char *argv[]) {
  CommandLineOptions options{argc, argv};

  if (!isFileExist(options.inputFileName())) {
    std::cerr << "File '" << options.inputFileName()
              << "' does not exist or it is not a regular file." << std::endl;
    return 1;
  }

  auto stream = std::ifstream{options.inputFileName()};
  auto d = Diagram{stream};
  diagram2png(d, options.outputFileName(), 24.0, options.isDebugMode());

  return 0;
}
