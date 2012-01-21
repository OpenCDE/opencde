#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <motifmm.h>
#include <opencde.h>

class FileWindow;
class Item;
class Rectangle;
class FileView : public Motif::Custom
{
private:
  int hiddenCount;
  FileWindow* fileWindow;
  Motif::Panel* panel;
  Motif::ScrollBar* scroll;
  int virtualHeight;
  GC xorGC;
  int oldY;
  int oldX;
  int startX;
  int startY;
  std::auto_ptr<Rectangle> selectionRect;
  OpenCDE::Ini* ini;
  XFontStruct* fontInfo;
  int lastClickTime;
  std::string path;

  Motif::auto_vector<Item> items;
  void drawSelectionRectangle(GC theGC, Rectangle* rect);
  void makeSelections();

  std::vector<Pixmap> typePixmaps;
  std::vector<std::string> typeNames;
  Pixmap buffer;

public:
  FileView(std::string name, Motif::Panel* panel, Motif::ScrollBar* scroll, OpenCDE::Ini* ini, FileWindow* fileWindow);
  ~FileView();

  virtual void onExpose(Widget widget, XtPointer clientData, XtPointer callData);
  virtual void onResize(Widget widget, XtPointer clientData, XtPointer callData);
  virtual void onMotion(Widget widget, XtPointer clientData, XEvent* callData);
  virtual void onArm(Widget widget, XtPointer clientData, XEvent* callData);
  virtual void onDisarm(Widget widget, XtPointer clientData, XEvent* callData);

  void redraw();
  void onDoubleClick();
  void setPath(std::string path);
  std::string getPath();
  Motif::auto_vector<Item>* getItems();
  Pixmap getPixmapForType(std::string typeName);
  int getHiddenCount();

};

#endif

