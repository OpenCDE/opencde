#include <opencde.h>

namespace OpenCDE
{

bool Filesystem::fileExists(std::string path)
{
  FILE* file = NULL;
  
  file = fopen(path.c_str(), "r");
  
  if (file == NULL)
  {
    return false;
  }
  
  fclose(file);
  
  return true;
}

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

std::string Filesystem::pathToResource(std::string res, std::string application, Filesystem::OFSResType type)
{
  std::cout << application << " requested " << res << "\n";
  if(res.length() < 1)
  {
    throw OpenCDEException("the resource path '" + res + "' is invalid");
  }
  
  if (res[0] == '/')
  {
    return res;
  }
  
  /* first try the user's path, then try the default path */
  std::string path;
  switch (type)
  {
    case Filesystem::ICON:
      path = Environment::getHome() + "/.opencde/" + application + "/icons/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      path = Environment::getPrefix() + "/" + application + "/icons/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      path = Environment::getHome() + "/.opencde/icons/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      path = Environment::getPrefix() + "/icons/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      return "";
    case Filesystem::BACKDROP:
      path = Environment::getHome() + "/.opencde/" + application + "/backdrops/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      path = Environment::getPrefix() + "/" + application + "/backdrops/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      path = Environment::getHome() + "/.opencde/backdrops/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      path = Environment::getPrefix() + "/backdrops/" + res;
      if (Filesystem::fileExists(path))
      {
        return path;
      }
      
      return "";
  }
  
  return NULL;
}
}
