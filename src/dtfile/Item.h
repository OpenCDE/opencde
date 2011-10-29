#ifndef ITEM_H
#define ITEM_H

#include <motifmm.h>

class Rectangle;
class FileView;

class ItemType
{
public:
  static const int FILE = 0;
  static const int FOLDER = 1;

};

class Item
{
private:
  std::string name;
  std::string fileType;
  int type;
  Pixmap pixmap;
  FileView* fileView;
  GC theGC;
  std::auto_ptr<Rectangle> rect;
  std::auto_ptr<Rectangle> iconRect;
  std::auto_ptr<Rectangle> textRect;
  Widget widget;
  bool selected;
  int textWidth;
  int itemType;

  void drawRectangle(Pixmap buffer, Rectangle* rect, Pixel color);
  void drawRectangleNoBuffer(Rectangle* rect, Pixel color);
  void joinBoxes(Pixmap buffer, Rectangle* rect, Rectangle* rect2, Pixel color);
  void joinBoxesNoBuffer(Rectangle* rect, Rectangle* rect2, Pixel color);
  std::string getFileType(std::string name);

public:
  Item(FileView* fileView, int itemType, std::string name);
  ~Item();

  void draw(Pixmap buffer, int yOffset);
  bool isColliding(Rectangle* rectangle);
  bool isColliding(Rectangle* src, Rectangle* dest);
  Rectangle* getRectangle();
  void setSelected(bool selected, int yOffset);
  bool getSelected();
  int getItemType();
  std::string getName();
  std::string getFileType();
  void setTextWidth(int textWidth);

};

#endif

