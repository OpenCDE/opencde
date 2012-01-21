#ifndef MOTIFMM_MOTIFEXCEPTION_H
#define MOTIFMM_MOTIFEXCEPTION_H

#include <motifmm.h>

namespace Motif
{

class MotifException : public std::exception
{
private:
  std::string message;

public:
  MotifException(std::string message) throw()
  {
    this->message = message;
  }

  ~MotifException() throw()
  {

  }

  const char* what() const throw()
  {
    return message.c_str();
  }
};

}

#endif

