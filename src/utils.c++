#include "utils.h++"

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


bool isFileExist(const std::string filename) {
  struct stat file_info;
  if (stat(filename.c_str(), &file_info) != 0) return false;
  if (!S_ISREG(file_info.st_mode))             return false;
  return true;
}
