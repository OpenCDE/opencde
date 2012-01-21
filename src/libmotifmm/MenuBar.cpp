#include <motifmm.h>

namespace Motif
{

MenuBar::MenuBar(std::string name, Panel* panel)
{
  widget = XmCreateMenuBar(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  XtManageChild(widget);
}

MenuBar::~MenuBar()
{
  XtDestroyWidget(widget);
}

void MenuBar::setHelpMenu(PulldownMenu* pulldownMenu)
{
  Arg args[1];

  XtSetArg(args[0], XmNmenuHelpWidget, pulldownMenu->getCascadeButton());
  XtSetValues(widget, args, 1);
}

}

