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

  if(password->settingText == true)
  {
    return;
  }

  /* prevent paste operations by denying modifications >1 char */
  if(textBlock->length > 1)
  {
    callbackStruct->doit = False;
    return;
  }
  
  /* deletion.  Will delete from start position onwards. */
  if(callbackStruct->startPos < callbackStruct->endPos)
  {
    callbackStruct->endPos = password->text.size();
    password->text.resize(callbackStruct->startPos);
    return;
  }

  /* disallow insertions */
  if((unsigned) callbackStruct->startPos < password->text.size())
  {
    callbackStruct->doit = False;
    return;
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

