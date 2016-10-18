#pragma once

#include "diagram.h++"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <exception>
#include <string>
#include <ostream>


/// Tests that the statement throws the expected exception with the
/// provided description.
///
/// @param statement The statement to be tested.
/// @param expected_exception The expected type of the exception.
/// @prarm str The expected explanatory string (the value returned by
///   the `what()` member function of the thrown exception).
///
/// @warning The exception of type `expected_exception` must have a
/// `what()` member function similar to one used in `std::exception`.
#define EXPECT_THROW_WHATEQ(statement, expected_exception, str)         \
  do {                                                                  \
    try {                                                               \
      (statement);                                                      \
    } catch (expected_exception &e) {                                   \
      EXPECT_STREQ(e.what(), str);                                      \
      continue;                                                         \
    } catch (std::exception &e) {                                       \
      ADD_FAILURE() << "Exception of a wrong type was thrown." << std::endl \
                    << "Actual:   " << typeid(e).name() << std::endl    \
                    << "Expected: " << typeid(expected_exception).name() << std::endl; \
      continue;                                                         \
    } catch (...) {                                                     \
      ADD_FAILURE() << "Exception of a wrong non-derived from std::exception type was thrown."; \
      continue;                                                         \
    }                                                                   \
    ADD_FAILURE() << "Exception of type '"                              \
                  << typeid(expected_exception).name()                  \
                  << "' was not thrown.";                               \
  } while (0)


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
