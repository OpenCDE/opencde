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
  
  /**
   * Get the width of the first screen for the default display.
   * 
   * @see getScreenWidth(int)
   * @return width of screen in pixels
   */
  static int getScreenWidth();
  
  /**
   * Get the width of the given screen for the default display.
   * 
   * @param screen_number number of screen to get width of
   * @return width of screen in pixels
   */
  static int getScreenWidth(int screen_number);
  
  /**
   * Get the height of the first screen for the default display.
   * 
   * @see getScreenHeight(int)
   * @return height of the screen in pixels
   */
  static int getScreenHeight();
  
  /**
   * Get the height of the given screen for the default display.
   * 
   * @param screen_number number of screen to get height of
   * @return height of screen in pixels
   */
  static int getScreenHeight(int screen_number);

};

}

#endif

