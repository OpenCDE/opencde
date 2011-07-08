#include <motifmm.h>
#include <opencde.h>

#include "PanelWindow.h"

void safe_main(int argc, char* argv[])
{
  OpenCDE::Environment::initialize(argc, argv);

  Motif::Application::addFallbackResource("*highlightColor: #B24D7A");
  Motif::Application::addFallbackResource("*background: #AEB2C3");
  //Motif::Application::addFallbackResource("*panelWindow.background: Orange");
  Motif::Application::addFallbackResource("*exitDialog*fontList: -*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*desktopsPanel*desktopButton.background: #6366AB");
  Motif::Application::addFallbackResource("*desktopsPanel*fontList: -*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*menuWindow*fontList: -*-helvetica-*-r-*-*-13-*-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*menuWindow*foreground: White");

  Motif::Application::initialize("Dtpanel", argc, argv);

  try
  {
    new PanelWindow();
  }
  catch(std::exception& e)
  {
    //Motif::MessageBox::show("exceptionMessageBox", e.what(), "Exception", Motif::MessageBoxType::ERROR);
    new OpenCDE::ExceptionDialog(e.what(), "No additional information");
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

