#ifndef MOTIFMM_DIALOG_H
#define MOTIFMM_DIALOG_H

#include <motifmm.h>
#include <motifmm/Container.h>

namespace Motif
{

class Dialog : public Container
{
protected:

public:
  Dialog(std::string name);
  virtual ~Dialog();

};

}

#endif

