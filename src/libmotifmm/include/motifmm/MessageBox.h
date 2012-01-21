#ifndef MOTIFMM_MESSAGEBOX_H
#define MOTIFMM_MESSAGEBOX_H

#include <motifmm.h>

namespace Motif
{

struct MessageBoxType
{
public:
  static const int INFORMATION = 0;
  static const int ERROR = 1;
  static const int WARNING = 2;
  static const int QUESTION = 3;
};

class MessageBox
{
public:
  static void show(std::string name, std::string message, std::string title, int messageBoxType);

};

}

#endif

