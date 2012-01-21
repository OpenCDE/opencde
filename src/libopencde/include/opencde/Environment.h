#ifndef OPENCDE_ENVIRONMENT_H
#define OPENCDE_ENVIRONMENT_H

#include <opencde.h>

namespace OpenCDE
{

class Environment
{
private:
  static std::string prefix;
  static std::string name;

public:
  static void initialize(int argc, char* argv[]);
  static std::string getUsername();
  static std::string getVariable(std::string variable);
  static std::string getHostname();
  static std::string getPrefix();
  static std::string getName();
  static std::string getHome();

};

}

#endif

