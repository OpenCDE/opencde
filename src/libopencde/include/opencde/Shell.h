#ifndef OPENCDE_SHELL_H
#define OPENCDE_SHELL_H

#include <opencde.h>

namespace OpenCDE
{

class Shell
{
public:
  static void execute(std::string command);
  static void executeFork(std::string command);
  static std::string executeFetch(std::string command);

};

}

#endif

