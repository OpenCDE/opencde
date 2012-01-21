#ifndef GRAB_H
#define GRAB_H

#include <motifmm.h>

class Grab : public Motif::Custom
{
private:
  Motif::Window* window;
  int currentX;
  int currentY;

public:
  Grab(std::string name, Motif::Panel* panel, Motif::Window* window);
  ~Grab();

  virtual void onExpose(Widget widget, XtPointer clientData, XtPointer callData);
  virtual void onMotion(Widget widget, XtPointer clientData, XEvent* callData);
  virtual void onArm(Widget widget, XtPointer clientData, XEvent* callData);

};

#endif

