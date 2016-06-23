#include "test-utils.h++"

#include <cstdlib>

using namespace std;
using namespace testing;


ostream & operator << (ostream &s, const ElementClass &c) {
  switch (c) {
  case ElementClass::None:  s << "None";  break;
  case ElementClass::LineN: s << "LineN"; break;
  case ElementClass::LineW: s << "LineW"; break;
  case ElementClass::LineS: s << "LineS"; break;
  case ElementClass::LineE: s << "LineE"; break;
  default:
    cerr << "Unknown ElementClass = " << c << endl;
    abort();
  }
  return s;
}


ostream & operator << (ostream &s, const DiagramElement &e) {
  s << "c = '" << e.c << "', " << "classes = " << PrintToString(e.classes);
  return s;
}
