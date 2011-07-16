#include <motifmm.h>
#include <opencde.h>

#include "LoginWindow.h"

void split(int argc, char* argv[])
{
  int pid = 0;

  if(argc < 2 || std::string(argv[1]) != "-nodaemon")
  {
    pid = fork();
  }

  if(pid != 0)
  {
    exit(0);
  }

  while(true)
  {
    OpenCDE::Shell::execute("xinit " + OpenCDE::Environment::getPrefix() + "/share/opencde/dtlogin/scripts/xinitrc");
  }

  exit(0);
}

void safe_main(int argc, char* argv[])
{
  OpenCDE::Environment::initialize(argc, argv);

  if(OpenCDE::Environment::getUsername() != "root")
  {
    throw OpenCDE::OpenCDEException("This application must be run as root");
  }

  if(argc < 2)
  {
    split(argc, argv);
  }

  if(std::string(argv[1]) != "internal_dont_specify")
  {
    split(argc, argv);
  }

  Motif::Application::addFallbackResource("*highlightColor: #B24D7A");
  Motif::Application::addFallbackResource("*background: #AEB2C3");
  Motif::Application::addFallbackResource("*password.fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*usernameText.fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*okButton.fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*startOverButton.fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*informationLabel.fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*userInformationLabel.fontList: -*-fixed-*-*-*-20-*");
  Motif::Application::addFallbackResource("*usernameText.background: Gray50");
  Motif::Application::addFallbackResource("*password.background: Gray50");
  Motif::Application::addFallbackResource("*loginWindow.background: Black");
  Motif::Application::initialize("Dtlogin", argc, argv);

  try
  {
    new LoginWindow();
  }
  catch(std::exception& e)
  {
    Motif::MessageBox::show("exceptionMessageBox", e.what(), "Exception", Motif::MessageBoxType::ERROR);
  }

  Motif::Application::run();
}

int main(int argc, char* argv[])
{
  try
  {
    safe_main(argc, argv);

    return 0;
  }
  catch(std::exception& e)
  {
    std::cout << "Exception: " << e.what() << std::endl;

    return 1;
  }
}

