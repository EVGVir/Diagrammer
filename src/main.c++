#include "diagram.h++"
#include "drafting-table.h++"
#include "draw.h++"
#include "patterns.h++"

#include <iostream>
#include <string>


/// Saves a diagram into a PNG file.
///
/// @note All patterns are applied to the diagram, prio to its
/// rasterizing.
///
/// @param d Diagram to be saved.
/// @param filename File, the diagram to be saved to.
/// @param fontsize Font size that is used for rasterization.
void diagram2png(Diagram &d, const std::string &filename, double fontsize) {
  Patterns::applyAll(d);
  auto table = DraftingTable{d.width(), d.height(), fontsize};
  drawDiagram(d, table);
  table.saveToPNG(filename);
}


int main(int argc, char *argv[]) {
  auto d = Diagram{std::cin};
  diagram2png(d, "output.png", 24.0);
  return 0;
}
