#ifndef MOTIFMM_PANEL_H
#define MOTIFMM_PANEL_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Container;
class Panel : public Component
{
public:
  Panel(std::string name, Container* container);
  Panel(std::string name, Panel* panel);
  virtual ~Panel();

};

}

#endif

