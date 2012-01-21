#ifndef OPENCDE_FILESYSTEM_H
#define OPENCDE_FILESYSTEM_H

#include <opencde.h>

namespace OpenCDE
{
	
class Filesystem
{
private:

public:

  enum OFSResType
  {
    ICON,
    BACKDROP
  };
  
  static bool fileExists(std::string path);
  static bool folderExists(std::string path);
  static void copyFolder(std::string source, std::string destination);
  static void createFolder(std::string path);

  static std::string relativeFallback(std::string path, std::string fallback);
  
  static std::string pathToResource(std::string res, std::string application, OFSResType type);

};

}

#endif


