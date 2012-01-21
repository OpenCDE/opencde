#include <opencde.h>

namespace OpenCDE
{

void Shell::execute(std::string command)
{
  FILE* file = NULL;
  char buffer[128];
  std::string output;

  file = popen(std::string(command + " 2>&1").c_str(), "r");

  if(file == NULL)
  {
    throw OpenCDEException("Failed to execute `" + command + "`");
  }

  while(fgets(buffer, sizeof(buffer), file))
  {
    output += buffer;
  }

  if(pclose(file) != 0)
  {
    throw OpenCDEException(output);
  }
}

void Shell::executeFork(std::string command)
{
  system(std::string(command + " &").c_str());
}

std::string Shell::executeFetch(std::string command)
{
  FILE* file = NULL;
  char buffer[128];
  std::string output;

  file = popen(std::string(command + " 2>&1 | tr -d '\n'").c_str(), "r");

  if(file == NULL)
  {
    throw OpenCDEException("Failed to execute `" + command + "`");
  }

  while(fgets(buffer, sizeof(buffer), file))
  {
    output += buffer;
  }

  if(pclose(file) != 0)
  {
    throw OpenCDEException(output);
  }

  return output;
}

}

