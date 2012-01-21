#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>

class Rectangle
{
private:
  int x;
  int y;
  int width;
  int height;

public:
  Rectangle();
  Rectangle(int x1, int y1, int x2, int y2);
  ~Rectangle();

  int getX();
  int getY();
  int getWidth();
  int getHeight();
  void setWidth(int width);
  void setHeight(int height);
  void setX(int x);
  void setY(int y);

};

#endif

