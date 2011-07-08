#ifndef OPENCDE_OPENCDEEXCEPTION_H
#define OPENCDE_OPENCDEEXCEPTION_H

#include <opencde.h>

namespace OpenCDE
{

class OpenCDEException : public std::exception
{
private:
  std::string message;

public:
  OpenCDEException(std::string message) throw()
  {
    this->message = message;
  }

  ~OpenCDEException() throw()
  {

  }

  const char* what() const throw()
  {
    return message.c_str();
  }
};

}

#endif

