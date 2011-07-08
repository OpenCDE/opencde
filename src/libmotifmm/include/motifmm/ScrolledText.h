#ifndef MOTIFMM_SCROLLEDTEXT_H
#define MOTIFMM_SCROLLEDTEXT_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Panel;
class ScrolledText : public Component
{
public:
  ScrolledText(std::string name, Panel* panel);
  virtual ~ScrolledText();

};

}

#endif

