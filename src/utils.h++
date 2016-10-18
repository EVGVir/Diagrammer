#include <cstdlib>
#include <iostream>
#include <sstream>

/// Checks if condition is true. If it does not, assert outputs
/// diagnostic information on the standard error output and calls
/// std::abort().
///
/// @param condition Condition to be checked.
/// @param errorMessage A message to be printed before exit.
#define ASSERT(condition, errorMessage)                                 \
  do {                                                                  \
    if (!(condition)) {                                                 \
      std::cerr << __FILE__ << ":" << __LINE__                          \
                << ": Assertion `" #condition "` failed in function "   \
                << __func__ << "() with message:" << std::endl          \
                << (errorMessage) << std::endl;                         \
      std::abort();                                                     \
    }                                                                   \
  } while (false)


/// Checks if a file exists and it is a regular file.
///
/// @param filename Name of the file to be checked.
///
/// @return Result of the check.
/// @retval true  File exists and it is a regular file.
/// @retval false File does not exists or it is not a regular file.
bool isFileExist(const std::string filename);


/// @return Literal representation of a value.
/// @param value A value to be represented in form of a string.
///        Different types are converted in a different way:
///            Type |  Value |   Result
///        ---------+--------+---------
///         Integer |      5 |      "5"
///         Integer |   0123 |     "83"
///         Integer | 0xbeaf |  "48815"
///           Float |   3.14 |   "3.14"
///        C-string |  "abc" |    "abc"
///         Pointer | 0xbeaf | "0xbeaf"
template<typename T>
inline std::string toString(T value) {
  std::stringstream ss{std::ios_base::out};
  ss << value;
  return ss.str();
}


/// @return Concatenated literal representation of its parameters.
template<typename T, typename... Args>
inline std::string toString(T value, Args... values) {
  return toString(value) + toString(values...);
}
