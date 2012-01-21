#ifndef MOTIFMM_SEPARATOR_H
#define MOTIFMM_SEPARATOR_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class PulldownMenu;
class Separator : public Component
{
private:

public:
  Separator(std::string name, PulldownMenu* pulldownMenu);
  virtual ~Separator();

};

}

#endif

