#include <motifmm.h>
#include <opencde.h>

#include "RunWindow.h"

void safe_main(int argc, char* argv[])
{
  OpenCDE::Environment::initialize(argc, argv);
  Motif::Application::addFallbackResource("*shadowThickness: 1");
  Motif::Application::addFallbackResource("*highlightThickness: 2");
  Motif::Application::addFallbackResource("*highlightColor: #B24D7A");
  Motif::Application::addFallbackResource("*background: #AEB2C3");
  Motif::Application::addFallbackResource("*editorScrolledText.background: White");
  Motif::Application::initialize("Dtrun", argc, argv);

  try
  {
    new RunWindow();
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

