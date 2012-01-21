#include <opencde.h>

namespace OpenCDE
{

std::string Environment::prefix;
std::string Environment::name;

void Environment::initialize(int argc, char* argv[])
{
  std::string app = Shell::executeFetch("which " + std::string(argv[0]));
  std::string bin = Shell::executeFetch("dirname " + app);
  prefix = Shell::executeFetch("cd " + bin + "/..; pwd");
  name = app.substr(app.find_last_of('/') + 1);
#ifdef USE_FSH
  std::string conf = "/etc/opencde/" + name;
#else 
  std::string conf = prefix + "/etc/opencde/" + name;
#endif
  setenv("OPENCDE_PREFIX", prefix.c_str(), 1);

  if(Filesystem::folderExists(conf) == true)
  {
    if(Filesystem::folderExists(getHome() + "/.opencde") == false)
    {
      Filesystem::createFolder(getHome() + "/.opencde");
    }

    if(Filesystem::folderExists(getHome() + "/.opencde/" + name) == false)
    {
      Filesystem::copyFolder(conf, getHome() + "/.opencde/" + name);
    }
  }

  Motif::Application::addFallbackResource("*exceptionDialog.background: #1A1866");
  Motif::Application::addFallbackResource("*exceptionDialog*informationLabel.background: #1A1866");
  Motif::Application::addFallbackResource("*exceptionDialog*messageLabel.background: #1A1866");
  Motif::Application::addFallbackResource("*exceptionDialog*informationPanel*shadowThickness: 1");
  Motif::Application::addFallbackResource("*exceptionDialog*fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
}

std::string Environment::getUsername()
{
  return Shell::executeFetch("whoami");
}

std::string Environment::getVariable(std::string variable)
{
  return getenv(variable.c_str());
}

std::string Environment::getHostname()
{
  return Shell::executeFetch("hostname");
}

std::string Environment::getPrefix()
{
  return prefix;
}

std::string Environment::getName()
{
  return name;
}

std::string Environment::getHome()
{
  return getVariable("HOME");
}

}

