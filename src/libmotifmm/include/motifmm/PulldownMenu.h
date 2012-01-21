#ifndef MOTIFMM_PULLDOWNMENU_H
#define MOTIFMM_PULLDOWNMENU_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class MenuBar;
class PulldownMenu : public Component
{
private:
  Widget cascadeButton;

public:
  PulldownMenu(std::string name, MenuBar* menuBar);
  virtual ~PulldownMenu();

  virtual void setText(std::string text);
  virtual Widget getCascadeButton();

};

}

#endif

