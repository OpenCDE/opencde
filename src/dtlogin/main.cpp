#include <motifmm.h>
#include <opencde.h>
#include <unistd.h>

#include "LoginWindow.h"

void print_usage(const char *prgName);

void split(int argc, char* argv[], bool daemonize)
{
  int pid = 0;

  if(argc < 2 || daemonize)
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

  if(geteuid() != 0)
  {
    throw OpenCDE::OpenCDEException("This application must be run as root");
  }
  
  /* parse command line args */
  
  bool daemonize = true;
  bool internal = false;
  
  int i;
  char *prgName = argv[0];
  for (i = 0; i < argc; i++)
  {
    if (! strcmp("-nodaemon", argv[i]))
    {
      daemonize = false;
    }
    else if (! strcmp("-internal_dont_specify", argv[i]))
    {
      internal = true;
    }
    else if (! strcmp("-h", argv[i]) || i > 0)
    {
      /* unknown option, or -h specified */
      print_usage(prgName);
    }
  }

  if(! internal)
  {
    split(argc, argv, daemonize);
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

void print_usage(const char *prgName)
{
  std::cout << "Usage: " << std::string(prgName) << " [-nodaemon]" << std::endl;
  exit(0);
}
