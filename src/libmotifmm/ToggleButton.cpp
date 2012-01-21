#include <motifmm.h>

namespace Motif
{

void ToggleButton::armCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  ToggleButton* button = (ToggleButton*)client_data;

  if(button->armFunction.get() != NULL)
  {
    button->armFunction->execute(button);
  }
}

void ToggleButton::valueChangedCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  ToggleButton* button = (ToggleButton*)client_data;

  if(button->valueChangedFunction.get() != NULL)
  {
    button->valueChangedFunction->execute(button);
  }
}

void ToggleButton::disarmCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  ToggleButton* button = (ToggleButton*)client_data;

  if(button->disarmFunction.get() != NULL)
  {
    button->disarmFunction->execute(button);
  }
}

ToggleButton::ToggleButton(std::string name, Panel* panel)
{
  Arg args[2];

  XtSetArg(args[0], XmNindicatorOn, false);
  XtSetArg(args[1], XmNfillOnSelect, true);

  widget = XmCreateToggleButton(panel->getWidget(), (char*)name.c_str(), args, 2);
  XtAddCallback(widget, XmNvalueChangedCallback, valueChangedCallback, this);
  XtAddCallback(widget, XmNarmCallback, armCallback, this);
  XtAddCallback(widget, XmNdisarmCallback, disarmCallback, this);
  XtManageChild(widget);
}

ToggleButton::ToggleButton(std::string name, PulldownMenu* pulldownMenu)
{
  Arg args[2];

  XtSetArg(args[0], XmNindicatorOn, false);
  XtSetArg(args[1], XmNfillOnSelect, true);

  widget = XmCreateToggleButton(pulldownMenu->getWidget(), (char*)name.c_str(), args, 2);
  XtAddCallback(widget, XmNvalueChangedCallback, valueChangedCallback, this);
  XtAddCallback(widget, XmNarmCallback, armCallback, this);
  XtAddCallback(widget, XmNdisarmCallback, disarmCallback, this);
  XtManageChild(widget);
}

ToggleButton::~ToggleButton()
{
  XtDestroyWidget(widget);
}

void ToggleButton::setValueChangedFunction(Function* function)
{
  valueChangedFunction.reset(function);
}

void ToggleButton::setDisarmFunction(Function* function)
{
  disarmFunction.reset(function);
}

void ToggleButton::setArmFunction(Function* function)
{
  armFunction.reset(function);
}

}

