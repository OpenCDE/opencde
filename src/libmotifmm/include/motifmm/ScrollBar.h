#ifndef MOTIFMM_SCROLLBAR_H
#define MOTIFMM_SCROLLBAR_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class ScrollBar : public Component
{
private:
  static void valueChangedCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void dragCallback(Widget widget, XtPointer client_data, XtPointer call_data);

  std::auto_ptr<Function> valueChangedFunction;
  std::auto_ptr<Function> dragFunction;

public:
  ScrollBar(std::string name, Panel* panel);
  virtual ~ScrollBar();

  void setValueChangedFunction(Function* function);
  void setDragFunction(Function* function);

};

}

#endif

