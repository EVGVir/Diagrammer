#include "diagram.h++"

#include <istream>

using std::istream;
using std::make_pair;
using std::max;
using std::pair;
using std::string;


Diagram::Diagram(istream &input):
  mMatrix{0, 0}
{
  auto dim = getDimensions(input);
  mMatrix = {dim.first, dim.second};

  string line;

  for (size_t y{0}; y < height(); ++y) {
    getline(input, line);
    for (size_t x{0}; x < line.size(); ++x) {
      mMatrix[x][y] = DiagramElement {
        line[x],
        ElementClasses{ElementClass::None}
      };
    }
  }
}


const Matrix<DiagramElement>::Column & Diagram::operator [] (size_t x) {
  return mMatrix[x];
}


size_t Diagram::width() const {
  return mMatrix.width();
}


size_t Diagram::height() const {
  return mMatrix.height();
}


pair<size_t, size_t> Diagram::getDimensions(istream &input) {
  size_t width{0}, height{0};
  string line;

  while (!input.eof()) {
    ++height;
    getline(input, line);
    width = max(width, line.size());
  }
  input.clear();        // Seek does not work if flags aren't cleared.
  input.seekg(0);

  // Skip cariage return symbol at the end of file.
  if (line.size() == 0) --height;

  return make_pair(width, height);
}
