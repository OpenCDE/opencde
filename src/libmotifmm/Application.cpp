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

int Application::getScreenWidth()
{
  return XDisplayWidth(display, 0);
}

int Application::getScreenHeight()
{
  return XDisplayHeight(display, 0);
}

}

