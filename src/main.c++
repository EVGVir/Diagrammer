#include "diagram.h++"
#include "drafting-table.h++"
#include "draw.h++"
#include "patterns.h++"

#include <docopt.h>

#include <iostream>
#include <fstream>
#include <string>


/// This program 'usage' text.
static const char usage[] =
R"(Diagrammer - ASCII diagrams to pictures converter.

Usage:
  diagrammer [--debug] <input-file>
  diagrammer --help

Options:
  --debug, -d    Draw the diagram upon a grid.
  --help         Show this message and exit.

Copyright Evgeny Gagauz, 2016.
)";


/// Command line arguments (parsed by Docopt).
std::map<std::string, docopt::value> args;


/// Saves a diagram into a PNG file.
///
/// @note All patterns are applied to the diagram, prio to its
/// rasterizing.
///
/// @param d Diagram to be saved.
/// @param filename File, the diagram to be saved to.
/// @param fontsize Font size that is used for rasterization.
void diagram2png(Diagram &d, const std::string &filename, double fontsize) {
  applyAllPatterns(d);
  auto table = DraftingTable{d.width(), d.height(), fontsize};
  if (args["--debug"].asBool()) {
    table.drawMesh();
  }
  drawDiagram(d, table);
  table.saveToPNG(filename);
}


int main(int argc, char *argv[]) {
  args = docopt::docopt(usage, {argv + 1, argv + argc});

  auto stream = std::ifstream{args["<input-file>"].asString()};
  auto d = Diagram{stream};
  diagram2png(d, "output.png", 24.0);
  return 0;
}
