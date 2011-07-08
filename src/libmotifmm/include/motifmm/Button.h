#ifndef MOTIFMM_BUTTON_H
#define MOTIFMM_BUTTON_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class PulldownMenu;
class Button : public Component
{
private:
  static void armCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void activateCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void disarmCallback(Widget widget, XtPointer client_data, XtPointer call_data);

  std::auto_ptr<Function> armFunction;
  std::auto_ptr<Function> disarmFunction;
  std::auto_ptr<Function> activateFunction;

public:
  Button(std::string name, Panel* panel);
  Button(std::string name, PulldownMenu* pulldownMenu);
  virtual ~Button();

  void setActivateFunction(Function* function);
  void setArmFunction(Function* function);
  void setDisarmFunction(Function* function);

};

}

#endif

