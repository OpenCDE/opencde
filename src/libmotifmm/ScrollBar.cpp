#include <motifmm.h>

namespace Motif
{

void ScrollBar::valueChangedCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  ScrollBar* scroll = (ScrollBar*)client_data;

  if(scroll->valueChangedFunction.get() != NULL)
  {
    scroll->valueChangedFunction->execute(scroll);
  }
}

void ScrollBar::dragCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  ScrollBar* scroll = (ScrollBar*)client_data;

  if(scroll->dragFunction.get() != NULL)
  {
    scroll->dragFunction->execute(scroll);
  }
}

ScrollBar::ScrollBar(std::string name, Panel* panel)
{
  widget = XmCreateScrollBar(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  XtAddCallback(widget, XmNvalueChangedCallback, valueChangedCallback, this);
  XtAddCallback(widget, XmNdragCallback, dragCallback, this);
  XtManageChild(widget);
}

ScrollBar::~ScrollBar()
{
  XtDestroyWidget(widget);
}

void ScrollBar::setValueChangedFunction(Function* function)
{
  valueChangedFunction.reset(function);
}

void ScrollBar::setDragFunction(Function* function)
{
  dragFunction.reset(function);
}

}

