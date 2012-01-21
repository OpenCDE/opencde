#include <motifmm.h>

namespace Motif
{

Dialog::Dialog(std::string name) : Container(name)
{
  Arg args[1];

  XtSetArg(args[0], XmNdeleteResponse, XmDO_NOTHING);
  widget = XmCreateDialogShell(Application::getWidget(), (char*)Application::getName().c_str(), args, 1);

  deleteWindowAtom = XmInternAtom(XtDisplay(widget), (char*)"WM_DELETE_WINDOW", False);
  XmAddWMProtocolCallback(widget, deleteWindowAtom, closeCallback, (void*)this);
  XtAddEventHandler(widget, StructureNotifyMask, False, eventCallback, (void*)this);
  XtAddEventHandler(widget, FocusChangeMask, False, eventCallback, (void*)this);

  contentPanel.reset(new Panel(name, this));
  XtPopdown(widget);
}

Dialog::~Dialog()
{
  contentPanel.reset(NULL);
  // Delete deleteDialogAtom
  XtUnrealizeWidget(widget);
  XtDestroyWidget(widget);
}

}

