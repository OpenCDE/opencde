#ifndef MOTIFMM_TEXT_H
#define MOTIFMM_TEXT_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class Text : public Component
{
private:
  static void activateCallback(Widget widget, XtPointer client_data, XtPointer call_data);

  std::auto_ptr<Function> activateFunction;

public:
  Text(std::string name, Panel* panel);
  virtual ~Text();

  void setActivateFunction(Function* function);
  void setText(std::string text);
  std::string getText();

};

}

#endif

