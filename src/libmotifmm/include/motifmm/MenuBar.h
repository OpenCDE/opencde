#ifndef MOTIFMM_MENUBAR_H
#define MOTIFMM_MENUBAR_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class PulldownMenu;
class MenuBar : public Component
{
public:
  MenuBar(std::string name, Panel* panel);
  virtual ~MenuBar();

  virtual void setHelpMenu(PulldownMenu* pulldownMenu);

};

}

#endif

