#ifndef MOTIFMM_COMPONENT_H
#define MOTIFMM_COMPONENT_H

#include <motifmm.h>

namespace Motif
{

class IconPlacement
{
public:
  static const int TOP = XmIconTop;
  static const int LEFT = XmIconLeft;

};

class Attachment
{
public:
  static const int NONE = XmATTACH_NONE;
  static const int FORM = XmATTACH_FORM;
  static const int WIDGET = XmATTACH_WIDGET;
  static const int POSITION = XmATTACH_POSITION;

};

class LabelType
{
public:
  static const int PIXMAP = XmPIXMAP;

};

class ShadowType
{
public:
  static const int OUT = XmSHADOW_OUT;
  static const int IN = XmSHADOW_IN;
  static const int ETCHED_IN = XmSHADOW_ETCHED_IN;
  static const int ETCHED_OUT = XmSHADOW_ETCHED_OUT;

};

class Component
{
protected:
  Widget widget;
  std::string tag;

public:
  Component();
  virtual ~Component();

  virtual void setVisible(bool visible);
  virtual void setTitle(std::string title);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setTopAttachment(int attachment);
  virtual void setBottomAttachment(int attachment);
  virtual void setLeftAttachment(int attachment);
  virtual void setRightAttachment(int attachment);
  virtual void setTopWidget(Component* component);
  virtual void setBottomWidget(Component* component);
  virtual void setLeftWidget(Component* component);
  virtual void setRightWidget(Component* component);
  virtual void setTopOffset(int offset);
  virtual void setBottomOffset(int offset);
  virtual void setLeftOffset(int offset);
  virtual void setRightOffset(int offset);
  virtual void setTop(int top);
  virtual void setBottom(int bottom);
  virtual void setLeft(int left);
  virtual void setRight(int right);
  virtual void setShadowThickness(int shadowThickness);
  virtual void setHighlightThickness(int highlightThickness);
  virtual void setPixmap(std::string path);
  virtual void setIconPlacement(int iconPlacement);
  virtual void setText(std::string text);
  virtual void drawClockHands(XPoint* hour, XPoint* minute, int points);
  virtual void drawText(int x, int y, std::string text);
  virtual void setNoResize(bool noResize);
  virtual void setToggled(bool toggled);
  virtual bool getToggled();
  virtual void setResizable(bool resizable);
  virtual void setShadowType(int shadowType);
  virtual void setFocus();
  virtual void setSensitive(bool sensitive);
  virtual void setFillOnArm(bool fillOnArm);
  virtual void setShowAsDefault(int showAsDefault);
  virtual void setLabelType(int labelType);
  virtual void setLabelPixmap(std::string path, bool transparent = false);
  virtual void setTag(std::string tag);
  virtual std::string getTag();
  virtual void setBackground(Pixel pixel);
  virtual void setForeground(Pixel pixel);
  virtual void setBorderColor(Pixel pixel);
  virtual void setTopShadowColor(Pixel pixel);
  virtual void setBottomShadowColor(Pixel pixel);
  virtual void setHighlightColor(Pixel pixel);
  virtual void setArmColor(Pixel pixel);
  virtual Pixel getTopShadowColor();
  virtual Pixel getBottomShadowColor();
  virtual Pixel getHighlightColor();
  virtual Pixel getArmColor();
  virtual Pixel getBackground();
  virtual Pixel getForeground();

  virtual int getX();
  virtual int getY();
  virtual int getWidth();
  virtual int getHeight();
  virtual Widget getWidget();

};

}

#endif

