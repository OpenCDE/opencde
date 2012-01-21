#ifndef MOTIFMM_FUNCTION_H
#define MOTIFMM_FUNCTION_H

#include <motifmm.h>

#define FUNCTION(x) new Motif::ParameterFunction<typeof(*this)>(this, &x)

namespace Motif
{

class Function
{
private:

public:
  virtual ~Function(){}
  virtual void execute() = 0;
  virtual void execute(void* parameter) = 0;

};

template<typename T> class GenericFunction : public Function
{
private:
  T* instance;
  void (T::*funcPtr)();

public:
  GenericFunction(T* instance, void (T::*funcPtr)())
  {
    this->instance = instance;
    this->funcPtr = funcPtr;
  }

  virtual void execute()
  {
    (instance->*funcPtr)();
  }

  virtual void execute(void* parameter)
  {
    try
    {
      (instance->*funcPtr)();
    }
    catch(std::exception& e)
    {
      MessageBox::show("exceptionMessageBox", std::string("Exception: ") + e.what(), "Exception", MessageBoxType::ERROR);
    }
  }
};

template<typename T> class ParameterFunction : public Function
{
private:
  T* instance;
  void* parameter;
  void (T::*funcPtr)(void*);

public:
  ParameterFunction(T* instance, void (T::*funcPtr)(void*), void* parameter)
  {
    this->instance = instance;
    this->parameter = parameter;
    this->funcPtr = funcPtr;
  }

  ParameterFunction(T* instance, void (T::*funcPtr)(void*))
  {
    this->instance = instance;
    this->parameter = NULL;
    this->funcPtr = funcPtr;
  }

  virtual void execute(void* parameter)
  {
    try
    {
      (instance->*funcPtr)(parameter);
    }
    catch(std::exception& e)
    {
      MessageBox::show("exceptionMessageBox", std::string("Exception: ") + e.what(), "Exception", MessageBoxType::ERROR);
    }
  }

  virtual void execute()
  {
    (instance->*funcPtr)(parameter);
  }

};

}

#endif

