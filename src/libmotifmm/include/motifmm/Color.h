#ifndef MOTIFMM_COLOR_H
#define MOTIFMM_COLOR_H

#include <motifmm.h>

namespace Motif
{

class Color
{
private:
  Pixel pixel;

public:
  Color(std::string name);
  Color(Pixel pixel);
  ~Color();

  Pixel getPixel();
  Color getLighter();
  Color getDarker();

};

}

#endif

