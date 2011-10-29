#include <motifmm.h>

namespace Motif
{

Separator::Separator(std::string name, PulldownMenu* pulldownMenu)
{
  widget = XmCreateSeparator(pulldownMenu->getWidget(), (char*)name.c_str(), NULL, 0);
  XtManageChild(widget);
}

Separator::~Separator()
{
  XtDestroyWidget(widget);
}

}

