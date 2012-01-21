#include "Item.h"
#include "Rectangle.h"
#include "FileView.h"

Item::Item(FileView* fileView, int itemType, std::string name)
{
  this->itemType = itemType;
  textWidth = 0;
  this->fileView = fileView;
  rect.reset(new Rectangle());
  rect->setWidth(42);
  rect->setHeight(42);
  this->theGC = fileView->getGC();
  this->widget = fileView->getWidget();
  selected = false;
  iconRect.reset(new Rectangle());
  textRect.reset(new Rectangle());

  if(name == "..")
  {
    this->fileType = "dirup";
    this->name = "..(go up)";
    pixmap = fileView->getPixmapForType(fileType);
  }
  else if(itemType == ItemType::FOLDER)
  {
    this->name = name.substr(name.find_last_of('/')+1);
    this->fileType = "folder";
    pixmap = fileView->getPixmapForType(fileType);
  }
  else
  {
    this->name = name.substr(name.find_last_of('/')+1);
    this->fileType = getFileType(name);
    pixmap = fileView->getPixmapForType(fileType);
  }
}

Item::~Item()
{

}

int Item::getItemType()
{
  return itemType;
}

std::string Item::getFileType()
{
  return fileType;
}

std::string Item::getFileType(std::string name)
{
  std::string type;
  bool dotFound = false;

  for(int index = 0; index < name.length(); index++)
  {
    if(name[index] == '.')
    {
      type = "";
      dotFound = true;
    }
    else
    {
      type = type + name[index];
    }
  }

  if(dotFound == false)
  {
    return "";
  }

  return type;
}

void Item::draw(Pixmap buffer, int yOffset)
{
  iconRect->setWidth(40);
  iconRect->setHeight(39);
  iconRect->setX(rect->getX()+5);
  iconRect->setY(rect->getY() + yOffset + 5);

  if(selected == true)
  {
    drawRectangle(buffer, iconRect.get(), fileView->getHighlightColor());
  }

  //textRect->setWidth(rect->getWidth()-5);
  textRect->setWidth(textWidth);
  textRect->setHeight(22);
  textRect->setX(rect->getX()+5);
  textRect->setY(rect->getY() + yOffset + 37 + 6);

  if(selected == true)
  {
    drawRectangle(buffer, textRect.get(), fileView->getHighlightColor());
  }

  joinBoxes(buffer, iconRect.get(), textRect.get(), fileView->getBackground());

  XCopyArea(XtDisplay(widget), pixmap, buffer, theGC, 0, 0, 32, 32, iconRect->getX()+4, iconRect->getY()+4);

  XSetForeground(XtDisplay(widget), theGC, fileView->getForeground());
  XDrawString(XtDisplay(widget), buffer, theGC, textRect->getX() + 5, textRect->getY() + 15, name.c_str(), name.length());
}

void Item::drawRectangle(Pixmap buffer, Rectangle* rect, Pixel color)
{
  XSetForeground(XtDisplay(widget), theGC, color);

  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX(), rect->getY(), rect->getX() + rect->getWidth(), rect->getY());
  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX()+1, rect->getY()+1, rect->getX() + rect->getWidth()-1, rect->getY()+1);

  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX() + rect->getWidth(), rect->getY() + 1, rect->getX() + rect->getWidth(), rect->getY() + rect->getHeight()-1);
  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX() + rect->getWidth()-1, rect->getY()+2, rect->getX() + rect->getWidth()-1, rect->getY() + rect->getHeight()-1);

  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX(), rect->getY() + rect->getHeight(), rect->getX() + rect->getWidth(), rect->getY() + rect->getHeight());
  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX()+1, rect->getY() + rect->getHeight()-1, rect->getX() + rect->getWidth()-2, rect->getY() + rect->getHeight()-1);

  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX(), rect->getY()+1, rect->getX(), rect->getY() + rect->getHeight()-1);
  XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX()+1, rect->getY()+2, rect->getX()+1, rect->getY() + rect->getHeight()-2);
}

Rectangle* Item::getRectangle()
{
  return rect.get();
}

bool Item::isColliding(Rectangle* rectangle)
{
  if(isColliding(rectangle, iconRect.get()) == true)
  {
    return true;
  }

  if(isColliding(rectangle, textRect.get()) == true)
  {
    return true;
  }

  return false;
  //return isColliding(rectangle, rect.get());
}

bool Item::isColliding(Rectangle* src, Rectangle* dest)
{
  bool horiz = false;
  bool vert = false;

  if(src->getX() <= dest->getX())
  {
    if(src->getX() + src->getWidth() >= dest->getX())
    {
      horiz = true;
    }
  }
  else
  {
    if(dest->getX() + dest->getWidth() >= src->getX())
    {
      horiz = true;
    }
  }

  if(src->getY() <= dest->getY())
  {
    if(src->getY() + src->getHeight() >= dest->getY())
    {
      vert = true;
    }
  }
  else
  {
    if(dest->getY() + dest->getHeight() >= src->getY())
    {
      vert = true;
    }
  }

  if(vert == true && horiz == true)
  {
    return true;
  }

  return false;
}

void Item::setSelected(bool selected, int yOffset)
{
  yOffset = yOffset * -1;
  this->selected = selected;

  Rectangle icon;
  icon.setWidth(40);
  icon.setHeight(39);
  icon.setX(rect->getX()+5);
  icon.setY(rect->getY() + yOffset + 5);

  if(selected == true)
  {
    drawRectangleNoBuffer(&icon, fileView->getHighlightColor());
  }
  else
  {
    drawRectangleNoBuffer(&icon, fileView->getBackground());
  }

  Rectangle text;
  //text.setWidth(rect->getWidth()-5);
  text.setWidth(textWidth);
  text.setHeight(22);
  text.setX(rect->getX()+5);
  text.setY(rect->getY() + yOffset + 37 + 6);

  if(selected == true)
  {
    drawRectangleNoBuffer(&text, fileView->getHighlightColor());
  }
  else
  {
    drawRectangleNoBuffer(&text, fileView->getBackground());
  }

  joinBoxesNoBuffer(&icon, &text, fileView->getBackground());
}

void Item::joinBoxes(Pixmap buffer, Rectangle* rect, Rectangle* rect2, Pixel color)
{
  XSetForeground(XtDisplay(widget), theGC, color);

  if(rect->getWidth() < rect2->getWidth())
  {
    XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX()+2, rect->getY() + rect->getHeight(), rect->getX() + rect->getWidth()-2, rect->getY() + rect->getHeight());
    XDrawLine(XtDisplay(widget), buffer, theGC, rect->getX()+2, rect->getY()-1 + rect->getHeight(), rect->getX() + rect->getWidth() - 2, rect->getY()-1 + rect->getHeight());
  }
  else
  {
    XDrawLine(XtDisplay(widget), buffer, theGC, rect2->getX()+2, rect->getY() + rect->getHeight(), rect2->getX() + rect2->getWidth()-2, rect->getY() + rect->getHeight());
    XDrawLine(XtDisplay(widget), buffer, theGC, rect2->getX()+2, rect->getY()-1 + rect->getHeight(), rect2->getX() + rect2->getWidth() - 2, rect->getY()-1 + rect->getHeight());

  }
}

void Item::joinBoxesNoBuffer(Rectangle* rect, Rectangle* rect2, Pixel color)
{
  XSetForeground(XtDisplay(widget), theGC, color);
    
  if(rect->getWidth() < rect2->getWidth())
  {
    XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+2, rect->getY() + rect->getHeight(), rect->getX() + rect->getWidth()-2, rect->getY() + rect->getHeight());
    XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+2, rect->getY()-1 + rect->getHeight(), rect->getX() + rect->getWidth() - 2, rect->getY()-1+ rect->getHeight());
  }
  else
  {
    XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect2->getX()+2, rect->getY() + rect->getHeight(), rect2->getX() + rect2->getWidth()-2, rect->getY() + rect->getHeight());
    XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect2->getX()+2, rect->getY()-1 + rect->getHeight(), rect2->getX() + rect2->getWidth() - 2, rect->getY()-1+ rect->getHeight());
  }
}

void Item::drawRectangleNoBuffer(Rectangle* rect, Pixel color)
{
  XSetForeground(XtDisplay(widget), theGC, color);

  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX(), rect->getY(), rect->getX() + rect->getWidth(), rect->getY());
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+1, rect->getY()+1, rect->getX() + rect->getWidth()-1, rect->getY()+1);

  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX() + rect->getWidth(), rect->getY() + 1, rect->getX() + rect->getWidth(), rect->getY() + rect->getHeight()-1);
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX() + rect->getWidth()-1, rect->getY()+2, rect->getX() + rect->getWidth()-1, rect->getY() + rect->getHeight()-1);

  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX(), rect->getY() + rect->getHeight(), rect->getX() + rect->getWidth(), rect->getY() + rect->getHeight());
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+1, rect->getY() + rect->getHeight()-1, rect->getX() + rect->getWidth()-2, rect->getY() + rect->getHeight()-1);

  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX(), rect->getY()+1, rect->getX(), rect->getY() + rect->getHeight()-1);
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+1, rect->getY()+2, rect->getX()+1, rect->getY() + rect->getHeight()-2);
}

std::string Item::getName()
{
  return name;
}

void Item::setTextWidth(int textWidth)
{
  this->textWidth = textWidth;
}

bool Item::getSelected()
{
  return selected;
}

