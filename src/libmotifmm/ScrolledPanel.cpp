#include <motifmm.h>

namespace Motif
{

ScrolledPanel::ScrolledPanel(std::string name, Container* container)
{
  Arg args[2];

  XtSetArg(args[0], XmNscrollingPolicy, XmAUTOMATIC);
  XtSetArg(args[1], XmNvisualPolicy, XmCONSTANT);
  widget = XmCreateScrolledWindow(container->getWidget(), (char*)name.c_str(), args, 2);
  XtManageChild(widget);
}

ScrolledPanel::ScrolledPanel(std::string name, Panel* panel)
{
  Arg args[2];

  XtSetArg(args[0], XmNscrollingPolicy, XmAUTOMATIC);
  XtSetArg(args[1], XmNvisualPolicy, XmCONSTANT);
  widget = XmCreateScrolledWindow(panel->getWidget(), (char*)name.c_str(), args, 2);
  XtManageChild(widget);

  //Widget s;
  //s = XmCreateScrollBar(widget, "scroll", NULL, 0);
  //XtManageChild(s);
}

ScrolledPanel::~ScrolledPanel()
{
  //XtUnmanageChild(widget);
  //XtUnrealizeWidget(widget);
  XtDestroyWidget(widget);
}

}

