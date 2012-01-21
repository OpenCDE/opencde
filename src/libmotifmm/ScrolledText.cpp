#include <motifmm.h>

namespace Motif
{

ScrolledText::ScrolledText(std::string name, Panel* panel)
{
  Arg args[5];

  XtSetArg(args[0], XmNeditMode, XmMULTI_LINE_EDIT);
  XtSetArg(args[1], XmNrightAttachment, XmATTACH_FORM);
  XtSetArg(args[2], XmNleftAttachment, XmATTACH_FORM);
  XtSetArg(args[3], XmNtopAttachment, XmATTACH_FORM);
  XtSetArg(args[4], XmNbottomAttachment, XmATTACH_FORM);

  widget = XmCreateScrolledText(panel->getWidget(), (char*)name.c_str(), args, 5);
  XtManageChild(widget);
  std::cout << "Warning: ScrolledText is buggy and the attachments can't be changed" << std::endl;
  std::cout << "         after the component has been created. Make sure it is put" << std::endl;
  std::cout << "         in a panel because it will expand." << std::endl;
}

ScrolledText::~ScrolledText()
{
  XtDestroyWidget(widget);
}

}

