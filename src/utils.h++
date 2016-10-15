#include <cstdlib>
#include <iostream>


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
