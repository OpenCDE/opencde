#include <motifmm.h>

namespace Motif
{

Window::Window(std::string name) : Container(name)
{
  Arg args[1];

  XtSetArg(args[0], XmNdeleteResponse, XmDO_NOTHING);
  widget = XtAppCreateShell(Application::getName().c_str(), Application::getName().c_str(), applicationShellWidgetClass, Application::getDisplay(), args, 1);

  deleteWindowAtom = XmInternAtom(XtDisplay(widget), (char*)"WM_DELETE_WINDOW", False);
  XmAddWMProtocolCallback(widget, deleteWindowAtom, closeCallback, (void*)this);
  XtAddEventHandler(widget, StructureNotifyMask, False, eventCallback, (void*)this);
  XtAddEventHandler(widget, FocusChangeMask, False, eventCallback, (void*)this);

  contentPanel.reset(new Panel(name, this));
}

Window::~Window()
{
  // Delete deleteWindowAtom

  contentPanel.reset(NULL);

  XtPopdown(widget);
  XtUnrealizeWidget(widget);
  XtDestroyWidget(widget);
}

}

