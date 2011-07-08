#ifndef MOTIFMM_TOGGLEBUTTON_H
#define MOTIFMM_TOGGLEBUTTON_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class PulldownMenu;
class ToggleButton : public Component
{
private:
  static void armCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void valueChangedCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void disarmCallback(Widget widget, XtPointer client_data, XtPointer call_data);

  std::auto_ptr<Function> armFunction;
  std::auto_ptr<Function> disarmFunction;
  std::auto_ptr<Function> valueChangedFunction;

public:
  ToggleButton(std::string name, Panel* panel);
  ToggleButton(std::string name, PulldownMenu* pulldownMenu);
  virtual ~ToggleButton();

  void setValueChangedFunction(Function* function);
  void setArmFunction(Function* function);
  void setDisarmFunction(Function* function);

};

}

#endif

