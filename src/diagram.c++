#include "diagram.h++"

#include <cassert>
#include <istream>

using std::istream;
using std::make_pair;
using std::max;
using std::pair;
using std::string;


bool DiagramElement::hasClass(ElementClass c) const {
  return classes.find(c) != classes.end();
}


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


bool Diagram::checkPattern(size_t pos_x, size_t pos_y, const Pattern &pattern) const {
  assert(pos_x + pattern.width()  <= width());
  assert(pos_y + pattern.height() <= height());

  for (size_t pat_x = 0; pat_x < pattern.width(); ++pat_x) {
    for (size_t pat_y = 0; pat_y < pattern.height(); ++pat_y) {
      auto pat_value = pattern[pat_x][pat_y];

      if (pat_value.c != 0 &&
          pat_value.c != mMatrix[pos_x + pat_x][pos_y + pat_y].c)
      {
        return false;
      }
    }
  }

  return true;
}


void Diagram::applyPatternAtPos(size_t pos_x, size_t pos_y, const Pattern &pattern) {
  assert(pos_x + pattern.width()  <= width());
  assert(pos_y + pattern.height() <= height());

  for (size_t x = 0; x < pattern.width(); ++x) {
    for (size_t y = 0; y < pattern.height(); ++y) {
      const auto classes = pattern[x][y].classes;
      mMatrix[pos_x + x][pos_y + y].classes.insert(classes.cbegin(), classes.cend());
    }
  }
}


void Diagram::applyPattern(const Pattern &pattern) {
  if (pattern.width() > width() ||
      pattern.height() > height())
  {
    return;
  }

  for (size_t x = 0; x <= width() - pattern.width(); ++x) {
    for (size_t y = 0; y <= height() - pattern.height(); ++y) {
      if (checkPattern(x, y, pattern)) {
        applyPatternAtPos(x, y, pattern);
      }
    }
  }
}
