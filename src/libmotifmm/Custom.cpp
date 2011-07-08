#include <motifmm.h>

namespace Motif
{

void Custom::motionCallback(Widget widget, XtPointer clientData, XEvent* callData, Boolean* unused)
{
  Custom* custom = (Custom*)clientData;

  custom->onMotion(widget, clientData, callData);
}

void Custom::armCallback(Widget widget, XtPointer clientData, XEvent* callData, Boolean* unused)
{
  Custom* custom = (Custom*)clientData;

  custom->onArm(widget, clientData, callData);
}

void Custom::disarmCallback(Widget widget, XtPointer clientData, XEvent* callData, Boolean* unused)
{
  Custom* custom = (Custom*)clientData;

  custom->onDisarm(widget, clientData, callData);
}

void Custom::exposeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
  Custom* custom = (Custom*)clientData;

  custom->onExpose(widget, clientData, callData);
}

Custom::Custom(std::string name, Panel* panel)
{
  widget = XmCreateDrawingArea(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  //XtAddCallback(widget, XmNactivateCallback, activateCallback, this);
  XtAddEventHandler(widget, ButtonPressMask, FALSE, armCallback, this);
  XtAddEventHandler(widget, ButtonReleaseMask, FALSE, disarmCallback, this);
  XtAddEventHandler(widget, ButtonMotionMask, FALSE, motionCallback, this);
  XtAddCallback(widget, XmNexposeCallback, exposeCallback, this);
  XtManageChild(widget);

  Arg args[2];
  Pixel foreground;
  Pixel background;
  XGCValues vals;

  XtSetArg(args[0], XmNforeground, &foreground);
  XtSetArg(args[1], XmNbackground, &background);
  XtGetValues(widget, args, 2);
  vals.foreground = foreground;
  vals.background = background;

  gc = XtGetGC(widget, GCForeground | GCBackground, &vals);
}

Custom::~Custom()
{

}

void Custom::onExpose(Widget widget, XtPointer clientData, XtPointer callData)
{
  XDrawLine(XtDisplay(widget), XtWindow(widget), gc, 0, 0, 300, 300);
}

void Custom::onArm(Widget widget, XtPointer clientData, XEvent* callData)
{
  //std::cout << "Armed" << std::endl;
}

void Custom::onDisarm(Widget widget, XtPointer clientData, XEvent* callData)
{
  //std::cout << "Disarmed" << std::endl;
}

void Custom::onMotion(Widget widget, XtPointer clientData, XEvent* callData)
{
  //std::cout << "Motion" << std::endl;
}

}

