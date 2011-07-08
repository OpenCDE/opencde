#include <motifmm.h>

namespace Motif
{

void MessageBox::show(std::string name, std::string message, std::string title, int messageBoxType)
{
  Arg args[4];
  Widget widget;

  XtSetArg(args[0], XmNmessageString, (XmStringCreateLtoR((char*)message.c_str(), XmSTRING_DEFAULT_CHARSET)));
  XtSetArg(args[1], XmNtitleString, (XmStringCreateLtoR((char*)title.c_str(), XmSTRING_DEFAULT_CHARSET)));
  XtSetArg(args[2], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);
  XtSetArg(args[3], XmNtitle, title.c_str());
  widget = XmCreateErrorDialog(Application::getWidget(), (char*)name.c_str(), args, 4);
  XtUnmanageChild(XmMessageBoxGetChild(widget, XmDIALOG_HELP_BUTTON));
  XtUnmanageChild(XmMessageBoxGetChild(widget, XmDIALOG_CANCEL_BUTTON));
  XtManageChild(widget);
  XtRealizeWidget(widget);
}

}

