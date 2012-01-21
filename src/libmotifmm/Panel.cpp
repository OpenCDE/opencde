#include <motifmm.h>

namespace Motif
{

Panel::Panel(std::string name, Container* container)
{
  Arg args[2];

  XtSetArg(args[0], XmNnoResize, true);
  XtSetArg(args[1], XmNresizable, false);
  widget = XmCreateForm(container->getWidget(), (char*)name.c_str(), args, 0);
  XtManageChild(widget);
}

Panel::Panel(std::string name, Panel* panel)
{
  Arg args[1];

  XtSetArg(args[0], XmNnoResize, False);
  widget = XmCreateForm(panel->getWidget(), (char*)name.c_str(), args, 1);
  XtManageChild(widget);

  //Widget s;
  //s = XmCreateScrollBar(widget, "scroll", NULL, 0);
  //XtManageChild(s);
}

Panel::~Panel()
{
  //XtUnmanageChild(widget);
  //XtUnrealizeWidget(widget);
  XtDestroyWidget(widget);
}

}

