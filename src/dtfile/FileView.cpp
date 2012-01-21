#include "FileView.h"
#include "FileWindow.h"
#include "Rectangle.h"
#include "Item.h"
#include <opencde.h>

FileView::FileView(std::string name, Motif::Panel* panel, Motif::ScrollBar* scroll, OpenCDE::Ini* ini, FileWindow* fileWindow) : Motif::Custom(name, panel)
{
  hiddenCount = 0;
  this->fileWindow = fileWindow;
  lastClickTime = 0;
  buffer = -1;
  this->ini = ini;
  this->panel = panel;
  this->scroll = scroll;
  selectionRect.reset(new Rectangle());

  virtualHeight = 500;
  oldX = 0;
  oldY = 0;
  startX = 0;
  startY = 0;

  XGCValues vals = { 0 };
  vals.foreground = getForeground();
  vals.background = getBackground();
  vals.function = GXxor;
  xorGC = XtGetGC(widget, GCForeground | GCBackground | GCFunction, &vals);

  fontInfo = NULL;
  fontInfo = XLoadQueryFont(XtDisplay(widget), "fixed");

  if(fontInfo == NULL)
  {
    throw Motif::MotifException("Failed to load the fixed font");
  }

  setPath(OpenCDE::Environment::getHome());
}

FileView::~FileView()
{

}

void FileView::makeSelections()
{
  Rectangle r;

  r.setX(selectionRect->getX());
  //r.setY(selectionRect->getY() + scroll->getValue());
  r.setY(selectionRect->getY());
  r.setWidth(selectionRect->getWidth());
  r.setHeight(selectionRect->getHeight());

  for(int index = 0; index < items.size(); index++)
  {
    if(items.at(index)->isColliding(&r) == true)
    {
      items.at(index)->setSelected(true, scroll->getValue());
    }
    else
    {
      items.at(index)->setSelected(false, scroll->getValue());
    }
  }
}

void FileView::drawSelectionRectangle(GC theGC, Rectangle* rect)
{
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX(), rect->getY(), rect->getX() + rect->getWidth(), rect->getY());
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+1, rect->getY()+1, rect->getX() + rect->getWidth()-1, rect->getY()+1);

  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX() + rect->getWidth(), rect->getY()+1, rect->getX() + rect->getWidth(), rect->getY() + rect->getHeight()-1);
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX() + rect->getWidth()-1, rect->getY()+2, rect->getX() + rect->getWidth()-1, rect->getY() + rect->getHeight()-1);

  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX(), rect->getY() + rect->getHeight(), rect->getX() + rect->getWidth(), rect->getY() + rect->getHeight());
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+1, rect->getY() + rect->getHeight()-1, rect->getX() + rect->getWidth()-2, rect->getY() + rect->getHeight()-1);

  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX(), rect->getY()+1, rect->getX(), rect->getY() + rect->getHeight()-1);
  XDrawLine(XtDisplay(widget), XtWindow(widget), theGC, rect->getX()+1, rect->getY()+2, rect->getX()+1, rect->getY() + rect->getHeight()-2);
  //redraw();
}

void FileView::onMotion(Widget widget, XtPointer clientData, XEvent* callData)
{
  selectionRect.reset(new Rectangle(startX, startY, oldX, oldY));
  drawSelectionRectangle(xorGC, selectionRect.get());

  oldX = callData->xbutton.x;
  oldY = callData->xbutton.y;

  selectionRect.reset(new Rectangle(startX, startY, oldX, oldY));
  makeSelections();
  drawSelectionRectangle(xorGC, selectionRect.get());
}

void FileView::onDisarm(Widget widget, XtPointer clientData, XEvent* callData)
{
  XButtonEvent* be = (XButtonEvent*)callData;

  try
  {

    selectionRect.reset(new Rectangle(startX, startY, oldX, oldY));

    drawSelectionRectangle(xorGC, selectionRect.get());
    makeSelections();

    if(be->time - lastClickTime < XtGetMultiClickTime(XtDisplay(widget)))
    {
      onDoubleClick();
    }

    lastClickTime = be->time;
  }
  catch(std::exception& e)
  {
    Motif::MessageBox::show("exceptionMessageBox", std::string("Exception: ") + e.what(), "Exception", Motif::MessageBoxType::ERROR);
  }
}

void FileView::onDoubleClick()
{
  Item* item = NULL;
  std::string command;

  for(int index = 0; index < items.size(); index++)
  {
    if(items.at(index)->getSelected() == true)
    {
      item = items.at(index);
    }
  }

  if(item != NULL)
  {
    if(item->getItemType() == ItemType::FOLDER)
    {
      if(item->getFileType() == "dirup")
      {
        setPath(path.substr(0, path.find_last_of("/")));
        redraw();
      }
      else
      {
        if(path == "/")
        {
          setPath("/" + item->getName());
        }
        else
        {
          setPath(path + "/" + item->getName());
        }
        redraw();
      }
    }
    else
    {
      try
      {
        command = ini->getValue("", item->getFileType(), "command");
      }
      catch(std::exception& e)
      {
        // Open the OpenWith... dialog
        //std::cout << "OpenWith..." << std::endl;
        std::cout << "OpenWith: Reason[NoAssignedCommand] FileType[" << item->getFileType() << "]" << std::endl;
        return;
      }

      try
      {
        OpenCDE::Shell::execute("which " + command);
      }
      catch(std::exception& e)
      {
        // Open the OpenWith... dialog
        //std::cout << "OpenWith..." << std::endl;
        std::cout << "OpenWith: Reason[CommandFailed] Command[" << command << "] FileType[" << item->getFileType() << "]" << std::endl;
        return;
      }

      OpenCDE::Shell::executeFork(command + " " + path + "/" + item->getName());
    }
  }
}

void FileView::onArm(Widget widget, XtPointer clientData, XEvent* callData)
{
  oldX = callData->xbutton.x;
  startX = callData->xbutton.x;
  startY = callData->xbutton.y;
  oldY = callData->xbutton.y;

  selectionRect.reset(new Rectangle(startX, startY, oldX, oldY));
  makeSelections();
  drawSelectionRectangle(xorGC, selectionRect.get());
}

void FileView::onExpose(Widget widget, XtPointer clientData, XtPointer callData)
{
  Motif::Color color(getBackground());
  Colormap cmap = DefaultColormapOfScreen(XtScreen(Motif::Application::getWidget()));
  Pixel background = { 0 };
  Pixel top = { 0 };
  Pixel bottom = { 0 };
  Pixel highlight = { 0 };
  //Pixmap buffer = { 0 };

  XmGetColors(XtScreen(Motif::Application::getWidget()), cmap, color.getPixel(), &background, &top, &bottom, &highlight);

  if(buffer == -1)
  {
    buffer = XCreatePixmap(XtDisplay(widget), XtWindow(widget), getWidth(), getHeight(), DefaultDepthOfScreen(XtScreen(widget)));
  }

  XSetForeground(XtDisplay(widget), gc, getBackground());
  XFillRectangle(XtDisplay(widget), buffer, gc, 0, 0, getWidth(), getHeight());
  XSetForeground(XtDisplay(widget), gc, getHighlightColor());

  for(int index = 0; index < items.size(); index++)
  {
    items.at(index)->draw(buffer, -scroll->getValue());
  }

  XCopyArea(XtDisplay(widget), buffer, XtWindow(widget), gc, 0, 0, getWidth(), getHeight(), 0, 0);
  //XFreePixmap(XtDisplay(widget), buffer);
}

void FileView::onResize(Widget widget, XtPointer clientData, XtPointer callData)
{
  int rowCount = 0;
  int columnCount = 0;
  int columnMax = 0;

  columnMax = getWidth() / items.at(0)->getRectangle()->getWidth();

  for(int index = 0; index < items.size(); index++)
  {
    items.at(index)->getRectangle()->setX(columnCount * items.at(index)->getRectangle()->getWidth());
    items.at(index)->getRectangle()->setY(rowCount * items.at(index)->getRectangle()->getHeight());
    columnCount++;

    if(columnCount >= columnMax)
    {
      rowCount++;
      columnCount = 0;
    }
  }

  rowCount++;
  virtualHeight = rowCount * items.at(0)->getRectangle()->getHeight();

  if(getHeight() > 0)
  {
    if(virtualHeight > getHeight())
    {
      if(scroll->getValue() >= virtualHeight - getHeight())
      {
        scroll->setValue(virtualHeight - getHeight());
      }

      scroll->setMaximum(virtualHeight);
      scroll->setSliderSize(getHeight());
    }
    else
    {
      scroll->setValue(0);
      scroll->setSliderSize(1);
      scroll->setMaximum(1);
    }
  }

  // This doesn't seem to have any effect?
  scroll->setIncrement(25);

  if(buffer != -1)
  {
    XFreePixmap(XtDisplay(widget), buffer);
    buffer = -1;
  }

  if(isRealized() == true)
  {
    redraw();
  }
}

void FileView::redraw()
{
  // Intoduces flickers? Not sure why
  //XClearArea(XtDisplay(widget), XtWindow(widget), 0, 0, 0, 0, True);

  // Clears small 1x1 block, no flicker...
  XClearArea(XtDisplay(widget), XtWindow(widget), getWidth()-1, 0, getWidth()-1, getHeight()-1, True);
}

void FileView::setPath(std::string path)
{
  std::vector<std::string> entries;
  std::vector<std::string> directories;
  DIR* dir = NULL;
  DIR* testDir = NULL;
  struct dirent* ent = NULL;
  int maxWidth = 0;

  if(path == "")
  {
    path = "/";
  }

  dir = opendir(path.c_str());

  if(dir == NULL)
  {
    throw OpenCDE::OpenCDEException("Failed to open directory '" + path + "'");
  }

  hiddenCount = -2;

  while((ent = readdir(dir)) != NULL)
  {
    if(ent->d_name[0] == '.')
    {
      hiddenCount++;
      continue;
    }

    testDir = opendir(std::string(path + std::string("/") + ent->d_name).c_str());

    if(testDir == NULL)
    {
      entries.push_back(ent->d_name);
    }
    else
    {
      closedir(testDir);
      directories.push_back(ent->d_name);
    }
  }

  closedir(dir);

  //entries.sort();
  //directories.sort();
  items.clear();

  if(path != "/")
  {
    items.add(new Item(this, ItemType::FOLDER, ".."));
  }

  for(int index = 0; index < directories.size(); index++)
  {
    if(directories.at(index) != "." && directories.at(index) != "..")
    {
      items.add(new Item(this, ItemType::FOLDER, path + "/" + directories.at(index)));
    }
  }

  for(int index = 0; index < entries.size(); index++)
  {
    if(entries.at(index) != "." && entries.at(index) != "..")
    {
      items.add(new Item(this, ItemType::FILE, path + "/" + entries.at(index)));
    }
  }

/*
  items.add(new Item(this, ".."));
  items.add(new Item(this, path + "/file1.txt"));
  items.add(new Item(this, path + "/file2.txt"));
  items.add(new Item(this, path + "/file3.txt"));
  items.add(new Item(this, path + "/file4.txt"));
  items.add(new Item(this, path + "/file5.txt"));
  items.add(new Item(this, path + "/file6.txt"));
  items.add(new Item(this, path + "/file7.txt"));
  items.add(new Item(this, path + "/file8.txt"));
  items.add(new Item(this, path + "/file9.cpp"));
  items.add(new Item(this, path + "/file10.txt"));
  items.add(new Item(this, path + "/file11.txt"));
  items.add(new Item(this, path + "/file12.somecrazyfiletype"));
  items.add(new Item(this, path + "/file14.txt"));
  items.add(new Item(this, path + "/file15.txt"));
  items.add(new Item(this, path + "/file16.txt"));
  items.add(new Item(this, path + "/file17.txt"));
  items.add(new Item(this, path + "/file18.txt"));
  //items.add(new Item(this, path + "/file19.cat"));
  items.add(new Item(this, path + "/file20.txt"));
  items.add(new Item(this, path + "/file213425436346.txt"));
  items.add(new Item(this, path + "/.txt"));
  items.add(new Item(this, path + "/cs"));
*/

  for(int index = 0; index < items.size(); index++)
  {
    items.at(index)->setTextWidth(8 + XTextWidth(fontInfo, items.at(index)->getName().c_str(), items.at(index)->getName().length()));
    //if(maxWidth < items.at(index)->getName().length() * (fontInfo->ascent + fontInfo->descent))
    if(maxWidth < 15 + XTextWidth(fontInfo, items.at(index)->getName().c_str(), items.at(index)->getName().length()))
    {
      //maxWidth = items.at(index)->getName().length() * (fontInfo->ascent + fontInfo->descent);
      maxWidth = 15 + XTextWidth(fontInfo, items.at(index)->getName().c_str(), items.at(index)->getName().length());
    }
  }

  for(int index = 0; index < items.size(); index++)
  {
    items.at(index)->getRectangle()->setHeight(64);
    items.at(index)->getRectangle()->setWidth(maxWidth);
  }

  //virtualHeight = 500;
  //scroll->setMaximum(virtualHeight);
  this->path = path;
  onResize(widget, NULL, NULL);
  fileWindow->onDirectoryChanged(this);
}

Pixmap FileView::getPixmapForType(std::string typeName)
{
  for(int index = 0; index < typeNames.size(); index++)
  {
    if(typeNames.at(index) == typeName)
    {
      return typePixmaps.at(index);
    }
  }

  std::string path;

  try
  {
    path = OpenCDE::Filesystem::relativeFallback(ini->getValue("", typeName, "pixmap"), OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps");
  }
  catch(OpenCDE::OpenCDEException& e)
  {
    path = OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Dtbin.m.pm";
  }

  Arg args[2];
  Pixmap p;
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

  typePixmaps.push_back(p);
  typeNames.push_back(typeName);

  return p;
}

std::string FileView::getPath()
{
  return path;
}

Motif::auto_vector<Item>* FileView::getItems()
{
  return &items;
}

int FileView::getHiddenCount()
{
  return hiddenCount;
}

