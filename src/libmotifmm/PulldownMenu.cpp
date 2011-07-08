#include <motifmm.h>

namespace Motif
{

PulldownMenu::PulldownMenu(std::string name, MenuBar* menuBar)
{
  Arg args[1];

  widget = XmCreatePulldownMenu(menuBar->getWidget(), (char*)name.c_str(), NULL, 0);
  XtSetArg(args[0], XmNsubMenuId, widget);
  cascadeButton = XmCreateCascadeButton(menuBar->getWidget(), (char*)name.c_str(), args, 1);
  XtManageChild(cascadeButton);
}

PulldownMenu::~PulldownMenu()
{
  XtDestroyWidget(widget);
}

Widget PulldownMenu::getCascadeButton()
{
  return cascadeButton;
}

void PulldownMenu::setText(std::string text)
{
  Arg args[1];

  XtSetArg(args[0], XmNlabelString, XmStringCreateLtoR((char*)text.c_str(), XmSTRING_DEFAULT_CHARSET));
  XtSetValues(cascadeButton, args, 1);
}

}

