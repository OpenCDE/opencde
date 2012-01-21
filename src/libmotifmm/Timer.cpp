#include <motifmm.h>

namespace Motif
{

void Timer::intervalCallback(XtPointer clientData, XtIntervalId* id)
{
  Timer* timer = (Timer*)clientData;
  timer->id = -1;

  if(timer->intervalFunction.get() != NULL)
  {
    timer->intervalFunction->execute(timer);
  }

  if(timer->stopped == false)
  {
    timer->setId(XtAppAddTimeOut(Application::getContext(), timer->getTime(), intervalCallback, clientData));
  }
}

Timer::Timer()
{
  stopped = true;
  id = -1;
  time = 0;
}

Timer::~Timer()
{
  stopped = true;
  intervalFunction.reset(NULL);

  if(id != -1)
  {
    XtRemoveTimeOut(id);
    id = -1;
  }
}

void Timer::start(int time)
{
  stopped = false;
  this->time = time;
  id = XtAppAddTimeOut(Application::getContext(), time, intervalCallback, this);
}

void Timer::stop()
{
  stopped = true;
  intervalFunction.reset(NULL);

  if(id != -1)
  {
    XtRemoveTimeOut(id);
    id = -1;
  }
}

void Timer::setIntervalFunction(Function* function)
{
  intervalFunction.reset(function);
}

int Timer::getTime()
{
  return time;
}

void Timer::setId(int id)
{
  this->id = id;
}

}

