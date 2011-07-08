#include <motifmm.h>

namespace Motif
{

void Password::activateCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  Password* password = (Password*)client_data;

  if(password->activateFunction.get() != NULL)
  {
    password->activateFunction->execute(password);
  }
}

void Password::modifyVerifyCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
  Password* password = (Password*)client_data;
  XmTextVerifyCallbackStruct* callbackStruct = (XmTextVerifyCallbackStruct*) call_data;
  XmTextBlock textBlock = callbackStruct->text;
  XmTextPosition textPosition = callbackStruct->currInsert;

  if(password->settingText == true)
  {
    return;
  }

  if(textBlock->length > 1)
  {
    callbackStruct->doit = False;
    return;
  }

  if(textBlock->length == 0)
  {
    callbackStruct->doit = False;
    return;
  }

  if(callbackStruct->startPos < callbackStruct->endPos)
  {
    //std::cout << "delete " << callbackStruct->startPos << " " << callbackStruct->endPos << std::endl;
  }

  password->text = password->text + textBlock->ptr[0];
  textBlock->ptr[0] = '*';
}

Password::Password(std::string name, Panel* panel)
{
  settingText = false;
  widget = XmCreateText(panel->getWidget(), (char*)name.c_str(), NULL, 0);
  XtAddCallback(widget, XmNactivateCallback, activateCallback, this);
  XtAddCallback(widget, XmNmodifyVerifyCallback, modifyVerifyCallback, this);
  XtManageChild(widget);
}

Password::~Password()
{
  XtDestroyWidget(widget);
}

void Password::setActivateFunction(Function* function)
{
  activateFunction.reset(function);
}

std::string Password::getText()
{
  return text;
}

void Password::setText(std::string text)
{
  settingText = true;
  this->text = text;
  XmTextSetString(widget, (char*)text.c_str());
  settingText = false;
}

}

