#include <motifmm.h>

namespace Motif
{

bool Application::initialized = false;
XtAppContext Application::context;
Widget Application::widget;
std::string Application::name;
Display* Application::display = NULL;
std::vector<std::string> Application::fallbackResources;

void Application::initialize(std::string name, int argc, char* argv[])
{
  String fallbacks[fallbackResources.size() + 1];
  XtToolkitInitialize();
  context = XtCreateApplicationContext();

  for(unsigned int resourceIndex = 0; resourceIndex < fallbackResources.size(); resourceIndex++)
  {
    fallbacks[resourceIndex] = (char*)fallbackResources.at(resourceIndex).c_str();
  }

  fallbacks[fallbackResources.size()] = NULL;

  XtAppSetFallbackResources(context, fallbacks);
  Application::name = name;

  display = XtOpenDisplay(context, NULL, name.c_str(), name.c_str(), NULL, 0, &argc, argv);

  if(display == NULL)
  {
    throw MotifException("Failed to open display");
  }

  initialized = true;

  widget = XtAppCreateShell(Application::getName().c_str(), Application::getName().c_str(), applicationShellWidgetClass, Application::getDisplay(), NULL, 0);

}

void Application::run()
{
  if(initialized == false)
  {
    throw MotifException("Application is not yet initialized");
  }

  XtAppMainLoop(context);
}

XtAppContext Application::getContext()
{
  if(initialized == false)
  {
    throw MotifException("Application is not yet initialized");
  }

  return context;
}

Widget Application::getWidget()
{
  if(initialized == false)
  {
    throw MotifException("Application is not yet initialized");
  }

  return widget;
}

std::string Application::getName()
{
  if(initialized == false)
  {
    throw MotifException("Application is not yet initialized");
  }

  return name;
}

Display* Application::getDisplay()
{
  if(initialized == false)
  {
    throw MotifException("Application is not yet initialized");
  }

  return display;
}

void Application::addFallbackResource(std::string fallbackResource)
{
  fallbackResources.push_back(fallbackResource);
}

void Application::addResources(std::string path)
{
  std::ifstream file;
  std::string line;

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    return;
  }

  while(file.eof() == false)
  {
    getline(file, line);
    addFallbackResource(line);
  }
}

int Application::getScreenWidth()
{
  return XDisplayWidth(display, 0);
}

int Application::getScreenWidth(int screen_number)
{  
  return XDisplayWidth(display, screen_number);
}

int Application::getScreenHeight()
{
  return XDisplayHeight(display, 0);
}

int Application::getScreenHeight(int screen_number)
{
  return XDisplayHeight(display, screen_number);
}

}
