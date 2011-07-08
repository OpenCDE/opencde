#include <opencde.h>

namespace OpenCDE
{

bool Filesystem::folderExists(std::string path)
{
  DIR* dir = NULL;

  dir = opendir(path.c_str());

  if(dir == NULL)
  {
    return false;
  }
  else
  {
    closedir(dir);

    return true;
  }
}

void Filesystem::createFolder(std::string path)
{
  Shell::execute("mkdir " + path);
}

void Filesystem::copyFolder(std::string source, std::string destination)
{
  Shell::execute("cp -r " + source + " " + destination);
}

std::string Filesystem::relativeFallback(std::string path, std::string fallback)
{
  if(path.length() < 1)
  {
    throw OpenCDEException("the path '" + path + "' is invalid");
  }

  if(path[0] == '/')
  {
    return path;
  }
  else
  {
    return fallback + "/" + path;
  }
}

}

