#ifndef MOTIFMM_LABEL_H
#define MOTIFMM_LABEL_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class Label : public Component
{
private:

public:
  Label(std::string name, Panel* panel);
  virtual ~Label();

};

}

#endif

