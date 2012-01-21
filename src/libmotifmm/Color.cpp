#include <motifmm.h>

namespace Motif
{

Color::Color(std::string name)
{
  XrmValue fromValue;
  XrmValue toValue;

  fromValue.addr = (char*)name.c_str();
  fromValue.size = strlen(name.c_str()) + 1;
  toValue.addr = (char*)NULL;

  XtConvertAndStore(Application::getWidget(), XmRString, &fromValue, XmRPixel, &toValue);

  if(toValue.addr != (XtPointer)0)
  {
    pixel = (*(Pixel*)toValue.addr);
  }
  else
  {
    throw MotifException("Invalid color name");
  }
}

Color::Color(Pixel pixel)
{
  this->pixel = pixel;
}

Color::~Color()
{

}

Color Color::getLighter()
{
  Colormap cmap = DefaultColormapOfScreen(XtScreen(Application::getWidget()));
  XColor color;

  color.flags = DoRed|DoGreen|DoBlue;
  XAllocColor(XtDisplay(Application::getWidget()), cmap, &color);
  color.pixel = pixel;

  color.red += 50;
  color.green += 50;
  color.blue += 50;

  //XQueryColor(XtDisplay(Application::getWidget()), cmap, &color);
  //XStoreColor(XtDisplay(Application::getWidget()), cmap, &color);
  //XAllocColor(XtDisplay(Application::getWidget()), cmap, &color);

  return Color(color.pixel);
}

Color Color::getDarker()
{
  XColor color;

  color.pixel = pixel;

  color.red -= 20;
  color.green -= 20;
  color.blue -= 20;

  return Color(color.pixel);
}

Pixel Color::getPixel()
{
  return pixel;
}

}

