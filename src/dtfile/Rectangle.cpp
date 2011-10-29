#include "Rectangle.h"

Rectangle::Rectangle()
{
  x = 0;
  y = 0;
  width = 0;
  height = 0;
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2)
{
  x = 0;
  y = 0;
  width = 0;
  height = 0;

  if(x1 > x2)
  {
    x = x2;
    width = x1 - x;
  }
  else
  {
    x = x1;
    width = x2 - x;
  }

  if(y1 > y2)
  {
    y = y2;
    height = y1 - y;
  }
  else
  {
    y = y1;
    height = y2 - y;
  }
}

Rectangle::~Rectangle()
{

}

int Rectangle::getWidth()
{
  return width;
}

int Rectangle::getHeight()
{
  return height;
}

int Rectangle::getX()
{
  return x;
}

int Rectangle::getY()
{
  return y;
}

void Rectangle::setWidth(int width)
{
  this->width = width;
}

void Rectangle::setHeight(int height)
{
  this->height = height;
}

void Rectangle::setX(int x)
{
  this->x = x;
}

void Rectangle::setY(int y)
{
  this->y = y;
}

