#ifndef MOTIF_CUSTOM_H
#define MOTIF_CUSTOM_H

#include <motifmm.h>

namespace Motif
{

class Custom : public Component
{
protected:
  GC gc;

public:
  static void exposeCallback(Widget widget, XtPointer clientData, XtPointer callData);
  static void motionCallback(Widget widget, XtPointer clientData, XEvent* callData, Boolean* unused);
  static void armCallback(Widget widget, XtPointer clientData, XEvent* callData, Boolean* unused);
  static void disarmCallback(Widget widget, XtPointer clientData, XEvent* callData, Boolean* unused);

  Custom(std::string name, Panel* panel);
  virtual ~Custom();

  virtual void onExpose(Widget widget, XtPointer clientData, XtPointer callData);
  virtual void onMotion(Widget widget, XtPointer clientData, XEvent* callData);
  virtual void onArm(Widget widget, XtPointer clientData, XEvent* callData);
  virtual void onDisarm(Widget widget, XtPointer clientData, XEvent* callData);

};

}

#endif

