#ifndef MOTIFMM_WINDOW_H
#define MOTIFMM_WINDOW_H

#include <motifmm.h>
#include <motifmm/Container.h>

namespace Motif
{

class Window : public Container
{
protected:

public:
  Window(std::string name);
  virtual ~Window();

};

}

#endif

