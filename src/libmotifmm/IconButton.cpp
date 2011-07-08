#include <motifmm.h>

namespace Motif
{

void IconButton::armCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  IconButton* button = (IconButton*)client_data;

  if(button->armFunction.get() != NULL)
  {
    button->armFunction->execute(button);
  }
}

void IconButton::activateCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  IconButton* button = (IconButton*)client_data;

  if(button->activateFunction.get() != NULL)
  {
    button->activateFunction->execute(button);
  }
}

void IconButton::disarmCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  IconButton* button = (IconButton*)client_data;

  if(button->disarmFunction.get() != NULL)
  {
    button->disarmFunction->execute(button);
  }
}

IconButton::IconButton(std::string name, Panel* panel)
{
  widget = XmCreateIconButton(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  XtAddCallback(widget, XmNactivateCallback, activateCallback, this);
  //XtAddCallback(widget, XmNarmCallback, armCallback, this);
  //XtAddCallback(widget, XmNdisarmCallback, disarmCallback, this);
  XtManageChild(widget);
}

IconButton::IconButton(std::string name, PulldownMenu* pulldownMenu)
{
  widget = XmCreatePushButton(pulldownMenu->getWidget(), (char*)name.c_str(), NULL, 0);
  XtAddCallback(widget, XmNactivateCallback, activateCallback, this);
  //XtAddCallback(widget, XmNarmCallback, armCallback, this);
  //XtAddCallback(widget, XmNdisarmCallback, disarmCallback, this);
  XtManageChild(widget);
}

IconButton::~IconButton()
{
  XtDestroyWidget(widget);
}

void IconButton::setActivateFunction(Function* function)
{
  activateFunction.reset(function);
}

void IconButton::setDisarmFunction(Function* function)
{
  disarmFunction.reset(function);
}

void IconButton::setArmFunction(Function* function)
{
  armFunction.reset(function);
}

void IconButton::setPixmap(std::string path)
{
  Arg args[2];
  Pixmap p;
  Pixmap m;
  Pixel back;
  XpmAttributes attr;

  XtVaGetValues(widget, XmNbackground, &back, NULL);
  XpmColorSymbol none_color = { NULL, (char*)"None", (Pixel)0 };
  none_color.pixel = back;

  attr.valuemask = XpmReturnPixels | XpmColorSymbols | XpmCloseness;
  attr.colorsymbols = &none_color;
  attr.numsymbols = 1;
  attr.closeness = 80000;

  XpmReadFileToPixmap(XtDisplay(widget), DefaultRootWindow(XtDisplay(widget)), (char*)path.c_str(), &p, &m, &attr);

  XtSetArg(args[0], XmNiconPlacement, XmIconLeft);
  XtSetArg(args[1], XmNpixmap, p);
  XtSetValues(widget, args, 2);

  //XSetClipMask(XtDisplay(widget), XmIconButton_pixmap_fill_gc(widget), m);
}

void IconButton::setLabelPixmap(std::string path, bool transparent)
{
  Arg args[1];
  Pixmap pixmap;
  Pixmap mask;
  Pixel back;
  Pixel arm;
  XpmAttributes attributes;
  XpmColorSymbol colorSymbol = { NULL, "None", (Pixel)0 };

  XtVaGetValues(widget, XmNbackground, &back, NULL);
  XtVaGetValues(widget, XmNarmColor, &arm, NULL);
  colorSymbol.pixel = back;
  attributes.valuemask = XpmReturnPixels | XpmColorSymbols | XpmCloseness;
  attributes.colorsymbols = &colorSymbol;
  attributes.numsymbols = 1;
  attributes.closeness = 80000;

  XpmReadFileToPixmap(XtDisplay(widget), DefaultRootWindow(XtDisplay(widget)), (char*)path.c_str(), &pixmap, NULL, &attributes);
  XtSetArg(args[0], XmNpixmap, pixmap);
  XtSetValues(widget, args, 1);

  if(transparent == true)
  {
    colorSymbol.pixel = arm;
    XpmReadFileToPixmap(XtDisplay(widget), DefaultRootWindow(XtDisplay(widget)), (char*)path.c_str(), &pixmap, &mask, &attributes);
    //XtSetArg(args[0], XmNarmPixmap, mask);
    //XtSetValues(widget, args, 1);
    XSetClipMask(XtDisplay(widget), XmIconButton_pixmap_fill_gc(widget), mask);
  std::cout << path << std::endl;
  }
}

}

