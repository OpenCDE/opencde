#include <motifmm.h>
#include <opencde.h>

#include "SplashDialog.h"

void safe_main(int argc, char* argv[])
{
  OpenCDE::Environment::initialize(argc, argv);
  Motif::Application::addFallbackResource("*highlightColor: #B24D7A");
  Motif::Application::addFallbackResource("*background: #1A1866");
  Motif::Application::addFallbackResource("*lockDialog*fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*lockDialog.background: Black");
  Motif::Application::addFallbackResource("*password.background: Gray50");
  Motif::Application::initialize("Dtsplash", argc, argv);

  try
  {
    new SplashDialog();
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

