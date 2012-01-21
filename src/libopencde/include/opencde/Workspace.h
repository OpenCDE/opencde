#ifndef OPENCDE_WORKSPACE_H
#define OPENCDE_WORKSPACE_H

#include <opencde.h>

int vdesk(int argc, Window winId, int deskNo);

namespace OpenCDE
{

class Workspace
{
public:
  static void moveToWorkspace(Window id, int workspace);
  static void setWorkspace(int workspace);
  static void setBackgroundPixmap(std::string path);

};

}

#endif

