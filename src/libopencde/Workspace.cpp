#include <opencde.h>

namespace OpenCDE
{

void Workspace::setWorkspace(int workspace)
{
  vdesk(2, 0, workspace);
}

void Workspace::moveToWorkspace(Window id, int workspace)
{
  vdesk(3, id, workspace);
}

void Workspace::setBackgroundPixmap(std::string path)
{
  Display* display = NULL;
  Pixmap pixmap;
  int screen = 0;

  display = XOpenDisplay(NULL);

  if(display == NULL)
  {
    return;
  }

  screen = DefaultScreen(display);

  XpmReadFileToPixmap(display, RootWindow(display, screen), (char*)path.c_str(), &pixmap, NULL, NULL);
  XSetWindowBackgroundPixmap(display, DefaultRootWindow(display), pixmap);
  XClearWindow(display, RootWindow(display, screen));
  XCloseDisplay(display);
}

}

