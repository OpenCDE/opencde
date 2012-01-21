#include <motifmm.h>

namespace Motif
{

void Button::armCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  Button* button = (Button*)client_data;

  if(button->armFunction.get() != NULL)
  {
    button->armFunction->execute(button);
  }
}

void Button::activateCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  Button* button = (Button*)client_data;

  if(button->activateFunction.get() != NULL)
  {
    button->activateFunction->execute(button);
  }
}

void Button::disarmCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  Button* button = (Button*)client_data;

  if(button->disarmFunction.get() != NULL)
  {
    button->disarmFunction->execute(button);
  }
}

Button::Button(std::string name, Panel* panel)
{
  widget = XmCreatePushButton(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  XtAddCallback(widget, XmNactivateCallback, activateCallback, this);
  XtAddCallback(widget, XmNarmCallback, armCallback, this);
  XtAddCallback(widget, XmNdisarmCallback, disarmCallback, this);
  XtManageChild(widget);
}

Button::Button(std::string name, PulldownMenu* pulldownMenu)
{
  widget = XmCreatePushButton(pulldownMenu->getWidget(), (char*)name.c_str(), NULL, 0);
  XtAddCallback(widget, XmNactivateCallback, activateCallback, this);
  XtAddCallback(widget, XmNarmCallback, armCallback, this);
  XtAddCallback(widget, XmNdisarmCallback, disarmCallback, this);
  XtManageChild(widget);
}

Button::~Button()
{
  XtDestroyWidget(widget);
}

void Button::setActivateFunction(Function* function)
{
  activateFunction.reset(function);
}

void Button::setDisarmFunction(Function* function)
{
  disarmFunction.reset(function);
}

void Button::setArmFunction(Function* function)
{
  armFunction.reset(function);
}

}

