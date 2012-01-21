#include <motifmm.h>
#include <opencde.h>

#include "LockDialog.h"

void safe_main(int argc, char* argv[])
{
  OpenCDE::Environment::initialize(argc, argv);
  Motif::Application::addFallbackResource("*highlightColor: #B24D7A");
  Motif::Application::addFallbackResource("*background: #AEB2C3");
  Motif::Application::addFallbackResource("*lockDialog*fontList: -*-fixed-*-*-*-*-*-120-*-*-*-*-*-*");
  Motif::Application::addFallbackResource("*lockDialog.background: Black");
  Motif::Application::addFallbackResource("*password.background: Gray50");
  Motif::Application::initialize("Dtlock", argc, argv);

  try
  {
    new LockDialog();
  }
  catch(std::exception& e)
  {
    //Motif::MessageBox::show("exceptionMessageBox", e.what(), "Exception", Motif::MessageBoxType::ERROR);
    new OpenCDE::ExceptionDialog(e.what(), "The probable cause for this exception is that\nOpenCDE has not been fully installed.\nThe 'dtlock' application must be set to 'rwxs'");
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

