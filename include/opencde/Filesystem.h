#ifndef OPENCDE_FILESYSTEM_H
#define OPENCDE_FILESYSTEM_H

#include <opencde.h>

namespace OpenCDE
{

class Filesystem
{
private:

public:
  static bool folderExists(std::string path);
  static void copyFolder(std::string source, std::string destination);
  static void createFolder(std::string path);

  static std::string relativeFallback(std::string path, std::string fallback);

};

}

#endif

