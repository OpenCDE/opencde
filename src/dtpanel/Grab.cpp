#include "Grab.h"

Grab::Grab(std::string name, Motif::Panel* panel, Motif::Window* window) : Motif::Custom(name, panel)
{
  currentX = 0;
  currentY = 0;
  this->window = window;
}

Grab::~Grab()
{

}

void Grab::onMotion(Widget widget, XtPointer clientData, XEvent* callData)
{
  XPointerMovedEvent* pme = (XPointerMovedEvent*)callData;

  int amountX = pme->x_root - currentX;
  int amountY = pme->y_root - currentY;

  window->setX(window->getX() + amountX);
  window->setY(window->getY() + amountY);

  currentX = pme->x_root;
  currentY = pme->y_root;
}

void Grab::onArm(Widget widget, XtPointer clientData, XEvent* callData)
{
  XPointerMovedEvent* pme = (XPointerMovedEvent*)callData;

  currentX = pme->x_root;
  currentY = pme->y_root;
}

void Grab::onExpose(Widget widget, XtPointer clientData, XtPointer callData)
{
  int height = getHeight();
  int width = getWidth();

Motif::Color color(getBackground());

  Colormap cmap = DefaultColormapOfScreen(XtScreen(Motif::Application::getWidget()));
  Pixel bg;
  Pixel top;
  Pixel btm;
  Pixel hig;
  XmGetColors(XtScreen(Motif::Application::getWidget()), cmap, color.getPixel(), &bg, &top, &btm, &hig);

  XSetForeground(XtDisplay(widget), gc, btm);

  for(int index = 0; index < height; index+=2)
  {
    XDrawLine(XtDisplay(widget), XtWindow(widget), gc, 0, index, width, index);
  }

  XSetForeground(XtDisplay(widget), gc, top);

  for(int index = 1; index < height; index+=2)
  {
    XDrawLine(XtDisplay(widget), XtWindow(widget), gc, 0, index, width, index);
  }
}
