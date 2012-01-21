#include <motifmm.h>

namespace Motif
{

void Text::activateCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  Text* text = (Text*)client_data;

  if(text->activateFunction.get() != NULL)
  {
    text->activateFunction->execute(text);
  }
}

Text::Text(std::string name, Panel* panel)
{
  widget = XmCreateText(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  XtAddCallback(widget, XmNactivateCallback, activateCallback, this);
  XtManageChild(widget);
}

Text::~Text()
{
  XtDestroyWidget(widget);
}

void Text::setActivateFunction(Function* function)
{
  activateFunction.reset(function);
}

void Text::setText(std::string text)
{  
  XmTextSetString(widget, (char*)text.c_str());
}

std::string Text::getText()
{
  char* value = XmTextGetString(widget);

  return value;
}

}

