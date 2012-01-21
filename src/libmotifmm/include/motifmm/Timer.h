#ifndef MOTIFMM_TIMER_H
#define MOTIFMM_TIMER_H

#include <motifmm.h>

namespace Motif
{

class Timer
{
protected:
  int id;
  int time;
  bool stopped;

  std::auto_ptr<Function> intervalFunction;

public:
  Timer();
  ~Timer();

  void start(int time);
  void stop();

  int getTime();
  void setId(int id);

  static void intervalCallback(XtPointer clientData, XtIntervalId* id);
  void setIntervalFunction(Function* function);

};

}

#endif

