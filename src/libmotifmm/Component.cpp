#include <motifmm.h>

namespace Motif
{

Component::Component()
{

}

Component::~Component()
{

}

void Component::setTitle(std::string title)
{
  Arg args[2];

  XtSetArg(args[0], XmNtitle, title.c_str());
  XtSetArg(args[1], XmNtitleString, (XmStringCreateLtoR((char*)title.c_str(), XmSTRING_DEFAULT_CHARSET)));
  XtSetValues(widget, args, 2);
}

void Component::setToggled(bool toggled)
{
  Arg args[1];

  XtSetArg(args[0], XmNset, toggled);
  XtSetValues(widget, args, 1);
}

bool Component::getToggled()
{
  bool toggled = false;
  Arg args[1];

  XtSetArg(args[0], XmNset, &toggled);
  XtGetValues(widget, args, 1);
  
  return toggled;
}

void Component::setVisible(bool visible)
{
  if(visible == true)
  {
    XtManageChild(widget);
  }
  else
  {
    XtUnmanageChild(widget);
  }
}

void Component::setTopWidget(Component* component)
{
  Arg args[1];

  XtSetArg(args[0], XmNtopWidget, component->getWidget());
  XtSetValues(widget, args, 1);
}

void Component::setBottomWidget(Component* component)
{
  Arg args[1];

  XtSetArg(args[0], XmNbottomWidget, component->getWidget());
  XtSetValues(widget, args, 1);
}

void Component::setLeftWidget(Component* component)
{
  Arg args[1];

  XtSetArg(args[0], XmNleftWidget, component->getWidget());
  XtSetValues(widget, args, 1);
}

void Component::setRightWidget(Component* component)
{
  Arg args[1];

  XtSetArg(args[0], XmNrightWidget, component->getWidget());
  XtSetValues(widget, args, 1);
}

void Component::setTopAttachment(int attachment)
{
  Arg args[1];

  XtSetArg(args[0], XmNtopAttachment, attachment);
  XtSetValues(widget, args, 1);
}

void Component::setBottomAttachment(int attachment)
{
  Arg args[1];

  XtSetArg(args[0], XmNbottomAttachment, attachment);
  XtSetValues(widget, args, 1);
}

void Component::setLeftAttachment(int attachment)
{
  Arg args[1];

  XtSetArg(args[0], XmNleftAttachment, attachment);
  XtSetValues(widget, args, 1);
}

void Component::setRightAttachment(int attachment)
{
  Arg args[1];

  XtSetArg(args[0], XmNrightAttachment, attachment);
  XtSetValues(widget, args, 1);
}

void Component::setTopOffset(int offset)
{
  Arg args[1];

  XtSetArg(args[0], XmNtopOffset, offset);
  XtSetValues(widget, args, 1);
}

void Component::setBottomOffset(int offset)
{
  Arg args[1];

  XtSetArg(args[0], XmNbottomOffset, offset);
  XtSetValues(widget, args, 1);
}

void Component::setLeftOffset(int offset)
{
  Arg args[1];

  XtSetArg(args[0], XmNleftOffset, offset);
  XtSetValues(widget, args, 1);
}

void Component::setRightOffset(int offset)
{
  Arg args[1];

  XtSetArg(args[0], XmNrightOffset, offset);
  XtSetValues(widget, args, 1);
}

void Component::setTop(int top)
{
  Arg args[2];

  XtSetArg(args[0], XmNtopAttachment, XmATTACH_FORM);
  XtSetArg(args[1], XmNtopOffset, top);
  XtSetValues(widget, args, 2);
}

void Component::setBottom(int bottom)
{
  Arg args[2];

  XtSetArg(args[0], XmNbottomAttachment, XmATTACH_FORM);
  XtSetArg(args[1], XmNbottomOffset, bottom);
  XtSetValues(widget, args, 2);
}

void Component::setLeft(int left)
{
  Arg args[2];

  XtSetArg(args[0], XmNleftAttachment, XmATTACH_FORM);
  XtSetArg(args[1], XmNleftOffset, left);
  XtSetValues(widget, args, 2);
}

void Component::setRight(int right)
{
  Arg args[2];

  XtSetArg(args[0], XmNrightAttachment, XmATTACH_FORM);
  XtSetArg(args[1], XmNrightOffset, right);
  XtSetValues(widget, args, 2);
}

void Component::setX(int x)
{
  Arg args[1];

  XtSetArg(args[0], XmNx, x);
  XtSetValues(widget, args, 1);
}

void Component::setY(int y)
{
  Arg args[1];

  XtSetArg(args[0], XmNy, y);
  XtSetValues(widget, args, 1);
}

void Component::setWidth(int width)
{
  Arg args[1];

  XtSetArg(args[0], XmNwidth, width);
  XtSetValues(widget, args, 1);
}

void Component::setHeight(int height)
{
  Arg args[1];

  XtSetArg(args[0], XmNheight, height);
  XtSetValues(widget, args, 1);
}

void Component::setShadowThickness(int shadowThickness)
{
  Arg args[1];
  
  XtSetArg(args[0], XmNshadowThickness, shadowThickness);
  XtSetValues(widget, args, 1);
}

void Component::setHighlightThickness(int highlightThickness)
{
  Arg args[1];
 
  XtSetArg(args[0], XmNhighlightThickness, highlightThickness);
  XtSetValues(widget, args, 1);
}

int Component::getX()
{
  Arg args[1];
  Position x = 0;

  XtSetArg(args[0], XmNx, &x);
  XtGetValues(widget, args, 1);

  return x;
}

int Component::getY()
{
  Arg args[1];
  Position y = 0;

  XtSetArg(args[0], XmNy, &y);
  XtGetValues(widget, args, 1);

  return y;
}

int Component::getWidth()
{
  Arg args[1];
  Dimension width = 0;

  XtSetArg(args[0], XmNwidth, &width);
  XtGetValues(widget, args, 1);

  return width;
}

int Component::getHeight()
{
  Arg args[1];
  Dimension height = 0;

  XtSetArg(args[0], XmNheight, &height);
  XtGetValues(widget, args, 1);

  return height;
}

Widget Component::getWidget()
{
  return widget;
}

void Component::setPixmap(std::string path)
{
  Arg args[2];
  Pixmap p = NULL;
  Pixel back;
  XpmAttributes attr;

  XtVaGetValues(widget, XmNbackground, &back, NULL);
  XpmColorSymbol none_color = { NULL, (char*)"None", (Pixel)0 };
  none_color.pixel = back;

  attr.valuemask = XpmReturnPixels | XpmColorSymbols | XpmCloseness;
  attr.colorsymbols = &none_color;
  attr.numsymbols = 1;
  attr.closeness = 80000;

  XpmReadFileToPixmap(XtDisplay(widget), DefaultRootWindow(XtDisplay(widget)), (char*)path.c_str(), &p, NULL, &attr);

  if(!p)
  {
    return;
  }

  XtSetArg(args[0], XmNlabelType, XmPIXMAP);
  XtSetArg(args[1], XmNlabelPixmap, p);
  XtSetValues(widget, args, 2);
}

void Component::setText(std::string text)
{
  XmString msg;
  Arg args[2];

  msg = XmStringCreateLtoR((char*)text.c_str(), XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[0], XmNlabelType, XmSTRING);
  XtSetArg(args[1], XmNlabelString, msg);
  XtSetValues(widget, args, 2);
}

void Component::setNoResize(bool noResize)
{
  Arg args[1];

  XtSetArg(args[0], XmNnoResize, noResize);
  XtSetValues(widget, args, 1);
}

void Component::setResizable(bool resizable)
{
  Arg args[1];

  XtSetArg(args[0], XmNresizable, resizable);
  XtSetValues(widget, args, 1);
}

void Component::setFocus()
{
  XmProcessTraversal(widget, XmTRAVERSE_CURRENT);
}

void Component::setSensitive(bool sensitive)
{
  XtSetSensitive(widget, sensitive);
}

void Component::setBackground(Pixel pixel)
{
  Arg args[1];

  XtSetArg(args[0], XmNbackground, pixel);
  XtSetValues(widget, args, 1);
}

void Component::setForeground(Pixel pixel)
{
  Arg args[1];

  XtSetArg(args[0], XmNforeground, pixel);
  XtSetValues(widget, args, 1);
}

void Component::setBorderColor(Pixel pixel)
{
  Arg args[1];

  XtSetArg(args[0], XmNborderColor, pixel);
  XtSetValues(widget, args, 1);
}

void Component::setTopShadowColor(Pixel pixel)
{
  Arg args[1];

  XtSetArg(args[0], XmNtopShadowColor, pixel);
  XtSetValues(widget, args, 1);
}

void Component::setBottomShadowColor(Pixel pixel)
{
  Arg args[1];

  XtSetArg(args[0], XmNbottomShadowColor, pixel);
  XtSetValues(widget, args, 1);
}

Pixel Component::getTopShadowColor()
{
  Pixel pixel = XmUNSPECIFIED_PIXEL;
  Arg args[1];

  XtSetArg(args[0], XmNtopShadowColor, &pixel);
  XtGetValues(widget, args, 1);

  return pixel;
}

Pixel Component::getBottomShadowColor()
{
  Pixel pixel = XmUNSPECIFIED_PIXEL;
  Arg args[1];

  XtSetArg(args[0], XmNbottomShadowColor, &pixel);
  XtGetValues(widget, args, 1);

  return pixel;
}

Pixel Component::getBackground()
{
  Pixel pixel = XmUNSPECIFIED_PIXEL;
  Arg args[1];

  XtSetArg(args[0], XmNbackground, &pixel);
  XtGetValues(widget, args, 1);

  return pixel;
}

Pixel Component::getForeground()
{
  Pixel pixel = XmUNSPECIFIED_PIXEL;
  Arg args[1];

  XtSetArg(args[0], XmNforeground, &pixel);
  XtGetValues(widget, args, 1);

  return pixel;
}

Pixel Component::getHighlightColor()
{
  Pixel pixel = XmUNSPECIFIED_PIXEL;
  Arg args[1];

  XtSetArg(args[0], XmNhighlightColor, &pixel);
  XtGetValues(widget, args, 1);

  return pixel;
}

Pixel Component::getArmColor()
{
  Pixel pixel = XmUNSPECIFIED_PIXEL;
  Arg args[1];

  XtSetArg(args[0], XmNarmColor, &pixel);
  XtGetValues(widget, args, 1);

  return pixel;
}

void Component::setHighlightColor(Pixel pixel)
{
  Arg args[1];

  XtSetArg(args[0], XmNhighlightColor, pixel);
  XtSetValues(widget, args, 1);
}

void Component::setArmColor(Pixel pixel)
{
  Arg args[1];

  XtSetArg(args[0], XmNarmColor, pixel);
  XtSetValues(widget, args, 1);
}

void Component::setLabelType(int labelType)
{
  Arg args[1];

  XtSetArg(args[0], XmNlabelType, labelType);
  XtSetValues(widget, args, 1);
}

void Component::setLabelPixmap(std::string path, bool transparent)
{
  Arg args[1];
  Pixmap pixmap = NULL;
  Pixmap mask = NULL;
  Pixel back;
  Pixel arm;
  XpmAttributes attributes;
  XpmColorSymbol colorSymbol = { NULL, (char*)"None", (Pixel)0 };

  XtVaGetValues(widget, XmNbackground, &back, NULL);
  XtVaGetValues(widget, XmNarmColor, &arm, NULL);
  colorSymbol.pixel = back;
  attributes.valuemask = XpmReturnPixels | XpmColorSymbols | XpmCloseness;
  attributes.colorsymbols = &colorSymbol;
  attributes.numsymbols = 1;
  attributes.closeness = 80000;

  XpmReadFileToPixmap(XtDisplay(widget), DefaultRootWindow(XtDisplay(widget)), (char*)path.c_str(), &pixmap, NULL, &attributes);

  if (!pixmap)
  {
    return;
  }

  XtSetArg(args[0], XmNlabelPixmap, pixmap);
  XtSetValues(widget, args, 1);

  if (transparent)
  {
    colorSymbol.pixel = arm;
    XpmReadFileToPixmap(XtDisplay(widget), DefaultRootWindow(XtDisplay(widget)), (char*)path.c_str(), &mask, NULL, &attributes);

    if (!mask)
    {
      return;
    }

    XtSetArg(args[0], XmNarmPixmap, mask);
    XtSetValues(widget, args, 1);
  }
}

void Component::setShadowType(int shadowType)
{
  Arg args[1];

  XtSetArg(args[0], XmNshadowType, shadowType);
  XtSetValues(widget, args, 1);
}

void Component::setFillOnArm(bool fillOnArm)
{
  Arg args[1];

  XtSetArg(args[0], XmNfillOnArm, fillOnArm);
  XtSetValues(widget, args, 1);
}

void Component::setShowAsDefault(int showAsDefault)
{
  Arg args[1];

  XtSetArg(args[0], XmNshowAsDefault, showAsDefault);
  XtSetValues(widget, args, 1);
}

std::string Component::getTag()
{
  return tag;
}

void Component::setTag(std::string tag)
{
  this->tag = tag;
}

void Component::setIconPlacement(int iconPlacement)
{
  Arg args[1];

  XtSetArg(args[0], XmNiconPlacement, iconPlacement);
  XtSetValues(widget, args, 1);
}

void Component::OBSOLETEdrawClockHands(XPoint* hour, XPoint* minute, int points)
{
  Arg args[2];
  GC gc;
  Pixmap p;

  XtSetArg(args[0], XmNlabelPixmap, &p);
  XtGetValues(widget, args, 1);

  Display *display = XtDisplay(widget);
  gc = XCreateGC(display, p, NULL, 0);
  XDrawLines(display, p, gc, hour,  points, CoordModeOrigin);
  XDrawLines(display, p, gc, minute,points, CoordModeOrigin);
  XFillPolygon(display, p, gc, hour,   points, Convex, CoordModeOrigin);
  XFillPolygon(display, p, gc, minute, points, Convex, CoordModeOrigin);
  //refreshPixmap();

  if(XtIsRealized(widget) == true)
  {
    XClearArea(XtDisplay(widget), XtWindow(widget), 0, 0, 1, 1, True);
  }
}

void Component::drawText(int x, int y, std::string text)
{
  Arg args[2];
  GC gc;
  Pixmap p;
  Display *display = XtDisplay(widget);

  XtSetArg(args[0], XmNlabelPixmap, &p);
  XtGetValues(widget, args, 1);

  gc = XCreateGC(display, p, NULL, 0);
  XDrawString(display, p, gc, x, y, text.c_str(), strlen(text.c_str()));

  XtSetArg(args[0], XmNlabelType, XmPIXMAP);
  XtSetArg(args[1], XmNlabelPixmap, p);
  XtSetValues(widget, args, 2);
}

int Component::getValue()
{
  Arg args[1];
  int value = 0;

  XtSetArg(args[0], XmNvalue, &value);
  XtGetValues(widget, args, 1);

  return value;
}

int Component::getMaximum()
{
  Arg args[1];
  int value = 0;

  XtSetArg(args[0], XmNmaximum, &value);
  XtGetValues(widget, args, 1);

  return value;
}

int Component::getMinimum()
{
  Arg args[1];
  int value = 0;

  XtSetArg(args[0], XmNminimum, &value);
  XtGetValues(widget, args, 1);

  return value;
}

int Component::getSliderSize()
{
  Arg args[1];
  int value = 0;

  XtSetArg(args[0], XmNsliderSize, &value);
  XtGetValues(widget, args, 1);

  return value;
}

void Component::setMaximum(int maximum)
{
  Arg args[2];

  //if(getValue() > maximum)
  //{
  //  setValue(maximum);
  //}

  XtSetArg(args[0], XmNmaximum, maximum);
  XtSetArg(args[1], XmNminimum, 0);
  XtSetValues(widget, args, 2);
}

void Component::setValue(int value)
{
  Arg args[1];

  XtSetArg(args[0], XmNvalue, value);
  XtSetValues(widget, args, 1);
}

void Component::setSliderSize(int sliderSize)
{
  Arg args[1];

  //if(sliderSize > getMaximum() - getMinimum())
  //{
  //  sliderSize = getMaximum() - getMinimum();
  //}

  XtSetArg(args[0], XmNsliderSize, sliderSize);
  XtSetValues(widget, args, 1);
}

void Component::setIncrement(int increment)
{
  Arg args[1];

  XtSetArg(args[0], XmNincrement, increment);
  XtSetValues(widget, args, 1);
}

void Component::setPageIncrement(int pageIncrement)
{
  Arg args[1];

  XtSetArg(args[0], XmNpageIncrement, pageIncrement);
  XtSetValues(widget, args, 1);
}

bool Component::isRealized()
{
  return XtIsRealized(widget);
}

void Component::setAccelerator(std::string accelerator)
{
  Arg args[1];

  XtSetArg(args[0], XmNaccelerator, accelerator.c_str());
  XtSetValues(widget, args, 1);
}

void Component::setAcceleratorText(std::string acceleratorText)
{
  Arg args[1];
  XmString txt = NULL;

  txt = XmStringCreateLocalized((char*)acceleratorText.c_str());
  XtSetArg(args[0], XmNacceleratorText, txt);
  XtSetValues(widget, args, 1);
  XmStringFree(txt);
}

}

