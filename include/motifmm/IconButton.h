#ifndef MOTIFMM_ICONBUTTON_H
#define MOTIFMM_ICONBUTTON_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class PulldownMenu;
class IconButton : public Component
{
private:
  static void armCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void activateCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void disarmCallback(Widget widget, XtPointer client_data, XtPointer call_data);

  std::auto_ptr<Function> armFunction;
  std::auto_ptr<Function> disarmFunction;
  std::auto_ptr<Function> activateFunction;

public:
  IconButton(std::string name, Panel* panel);
  IconButton(std::string name, PulldownMenu* pulldownMenu);
  virtual ~IconButton();

  virtual void setPixmap(std::string path);
  virtual void setLabelPixmap(std::string path, bool transparent);
  void setActivateFunction(Function* function);
  void setArmFunction(Function* function);
  void setDisarmFunction(Function* function);

};

}

#endif

