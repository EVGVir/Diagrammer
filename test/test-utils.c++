#include "test-utils.h++"

#include <cstdlib>

using namespace std;
using namespace testing;


ostream & operator << (ostream &s, const ElementClass &c) {
  switch (c) {
  case ElementClass::SolidLineN: s << "SolidLineN"; break;
  case ElementClass::SolidLineS: s << "SolidLineS"; break;
  case ElementClass::SolidLineE: s << "SolidLineE"; break;
  case ElementClass::SolidLineW: s << "SolidLineW"; break;
  case ElementClass::ArrowN:     s << "ArrowN";     break;
  case ElementClass::ArrowS:     s << "ArrowS";     break;
  case ElementClass::ArrowE:     s << "ArrowE";     break;
  case ElementClass::ArrowW:     s << "ArrowW";     break;
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
