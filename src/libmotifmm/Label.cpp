#include <motifmm.h>

namespace Motif
{

Label::Label(std::string name, Panel* panel)
{
  widget = XmCreateLabel(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  XtManageChild(widget);
}

Label::~Label()
{
  XtDestroyWidget(widget);
}

}

