#include <motifmm.h>

namespace Motif
{

void Container::closeCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  Container* container = (Container*)client_data;

  if(container->closeFunction.get() != NULL)
  {
    container->closeFunction->execute(container);
  }
}

void Container::eventCallback(Widget widget, XtPointer client_data, XEvent* event, Boolean* unused)
{
  Container* container = (Container*)client_data;

  if(event->type == 22)
  {
    if(container->lastWidth != container->getWidth() || container->lastHeight != container->getHeight())
    {
      if(container->resizeFunction.get() != NULL)
      {
        container->resizeFunction->execute(container);
      }

      container->lastWidth = container->getWidth();
      container->lastHeight = container->getHeight();
    }
    else
    {
      if(container->moveFunction.get() != NULL)
      {
        container->moveFunction->execute(container);
      }
    }
  }

  if(event->type == 18)
  {
    if(container->minimizeFunction.get() != NULL)
    {
      container->minimizeFunction->execute(container);
    }
  }

  if(event->type == 19)
  {
    if(container->showFunction.get() != NULL)
    {
      container->showFunction->execute(container);
    }
  }

  if(event->type == 9)
  {
    if(container->focusFunction.get() != NULL)
    {
      container->focusFunction->execute(container);
    }
  }

  if(event->type == 10)
  {
    if(container->unfocusFunction.get() != NULL)
    {
      container->unfocusFunction->execute(container);
    }
  }

  //std::cout << event->type << std::endl;
}

Container::Container(std::string name)
{
  lastWidth = 0;
  lastHeight = 0;
}

Container::~Container()
{

}

Panel* Container::getContentPanel()
{
  return contentPanel.get();
}

void Container::setCloseFunction(Function* function)
{
  closeFunction.reset(function);
}

void Container::setShowFunction(Function* function)
{
  showFunction.reset(function);
}

void Container::setMoveFunction(Function* function)
{
  moveFunction.reset(function);
}

void Container::setResizeFunction(Function* function)
{
  resizeFunction.reset(function);
}

void Container::setMinimizeFunction(Function* function)
{
  minimizeFunction.reset(function);
}

void Container::setFocusFunction(Function* function)
{
  focusFunction.reset(function);
}

void Container::setUnfocusFunction(Function* function)
{
  unfocusFunction.reset(function);
}

void Container::setDecorations(int decorations)
{
  Arg args[1];

  XtSetArg(args[0], XmNmwmDecorations, decorations);
  XtSetValues(widget, args, 1);
}

void Container::setStyle(int style)
{
  Arg args[1];

  XtSetArg(args[0], XmNdialogStyle, style);
  XtSetValues(getContentPanel()->getWidget(), args, 1);
}

void Container::setVisible(bool visible)
{
  if(visible == true)
  {
    //XtPopup(widget, XtGrabExclusive);
    XtPopup(widget, XtGrabNonexclusive);
  }
  else
  {
    XtPopdown(widget);
  }
}

void Container::setInitialFocus(Component* component)
{
  Arg args[1];

  XtSetArg(args[0], XmNinitialFocus, component->getWidget());
  XtSetValues(widget, args, 1);
}

void Container::setMovable(bool movable)
{
  Arg args[1];

  std::cout << "Warning: setMovable disables a lot more than just moving" << std::endl;
  XtSetArg(args[0], XmNmwmFunctions, 0);
  XtSetValues(widget, args, 1);
}

void Container::setMwmFunctions(int functions)
{
  Arg args[1];

  XtSetArg(args[0], XmNmwmFunctions, functions);
  XtSetValues(widget, args, 1);
}

void Container::unmap()
{
  XUnmapWindow(XtDisplay(widget), XtWindow(widget));
}

void Container::minimize()
{
  XIconifyWindow(XtDisplay(widget), XtWindow(widget), 0);
}

}

