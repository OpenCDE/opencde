#ifndef MOTIFMM_PASSWORD_H
#define MOTIFMM_PASSWORD_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class Password : public Component
{
private:
  static void activateCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void modifyVerifyCallback(Widget widget, XtPointer client_data, XtPointer call_data);

  std::string text;
  std::auto_ptr<Function> activateFunction;
  bool settingText;

public:
  Password(std::string name, Panel* panel);
  virtual ~Password();

  virtual void setActivateFunction(Function* function);

  virtual std::string getText();
  virtual void setText(std::string text);
};

}

#endif

