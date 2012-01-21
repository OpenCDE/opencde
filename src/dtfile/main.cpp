#include <motifmm.h>
#include <opencde.h>

#include "FileWindow.h"

void safe_main(int argc, char* argv[])
{
  OpenCDE::Environment::initialize(argc, argv);
  Motif::Application::addResources(OpenCDE::Environment::getPrefix() + "/share/opencde/app-defaults/Dtfile");

/*
  Motif::Application::addFallbackResource("*shadowThickness: 1");
  Motif::Application::addFallbackResource("*highlightThickness: 2");
  Motif::Application::addFallbackResource("*highlightColor: #B24D7A");
  Motif::Application::addFallbackResource("*background: #AEB2C3");
  Motif::Application::addFallbackResource("*fileView.background: #9397a5");
  Motif::Application::addFallbackResource("*fontList: -*-helvetica-*-r-*-*-12-*-*-*-*-*-*-*");
*/

  Motif::Application::initialize("Dtfile", argc, argv);

  try
  {
    if(argc > 1)
    {
      new FileWindow(std::string(argv[1]));
    }
    else
    {
      new FileWindow(OpenCDE::Environment::getHome());
    }
  }
  catch(std::exception& e)
  {
    new OpenCDE::ExceptionDialog(e.what(), "No additional information");
    //Motif::MessageBox::show("exceptionMessageBox", e.what(), "Exception", Motif::MessageBoxType::ERROR);
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

