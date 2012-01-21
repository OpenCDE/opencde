#ifndef MOTIFMM_SCROLLEDPANEL_H
#define MOTIFMM_SCROLLEDPANEL_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Container;
class ScrolledPanel : public Component
{
public:
  ScrolledPanel(std::string name, Container* container);
  ScrolledPanel(std::string name, Panel* panel);
  virtual ~ScrolledPanel();

};

}

#endif

