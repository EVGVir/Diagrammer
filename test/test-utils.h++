#pragma once

#include "diagram.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <ostream>


/// Matcher for class @ref DiagramElement.
MATCHER_P(DiagramElementEq, value,
          "Diagram element " + std::string(negation ? "isn't" : "is") +
          " equal to:\n          " + // Spaces are used to indent new line.
          testing::PrintToString(value))
{
  if (arg.c != value.c) return false;
  if (arg.classes != value.classes) return false;
  return true;
}


/// Google Test Printer for @ref ElementClass.
std::ostream & operator << (std::ostream &s, const ElementClass &c);

/// Google Test Printer for @ref DiagramElement.
std::ostream & operator << (std::ostream &s, const DiagramElement &e);
