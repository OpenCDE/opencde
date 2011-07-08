#ifndef MOTIFMM_APPLICATION_H
#define MOTIFMM_APPLICATION_H

#include <motifmm.h>

namespace Motif
{

class Application
{
private:
  static bool initialized;
  static XtAppContext context;
  static Widget widget;
  static std::string name;
  static Display* display;
  static std::vector<std::string> fallbackResources;

public:
  static void initialize(std::string name, int argc, char* argv[]);
  static void run();

  static XtAppContext getContext();
  static Widget getWidget();
  static std::string getName();
  static Display* getDisplay();
  static void addFallbackResource(std::string fallbackResource);
  static int getScreenWidth();
  static int getScreenHeight();

};

}

#endif

