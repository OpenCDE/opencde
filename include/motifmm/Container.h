#ifndef MOTIFMM_CONTAINER_H
#define MOTIFMM_CONTAINER_H

#include <motifmm.h>
#include <motifmm/Component.h>

namespace Motif
{

class Style
{
public:
  static const int SYSTEM = XmDIALOG_SYSTEM_MODAL;
  static const int APPLICATION = XmDIALOG_APPLICATION_MODAL;

};

class MwmFunctions
{
public:
  static const int NONE = 0;
  static const int ALL = MWM_FUNC_ALL;
  static const int RESIZE = MWM_FUNC_RESIZE;
  static const int MOVE = MWM_FUNC_MOVE;
  static const int MINIMIZE = MWM_FUNC_MINIMIZE;
  static const int MAXIMIZE = MWM_FUNC_MAXIMIZE;
  static const int CLOSE = MWM_FUNC_CLOSE;

};

class Decorations
{
public:
  static const int NONE = 0;
  static const int ALL = MWM_DECOR_ALL;
  static const int BORDER = MWM_DECOR_BORDER;
  static const int RESIZEH = MWM_DECOR_RESIZEH;
  static const int TITLE = MWM_DECOR_TITLE;
  static const int MENU = MWM_DECOR_MENU;
  static const int MINIMIZE = MWM_DECOR_MINIMIZE;
  static const int MAXIMIZE = MWM_DECOR_MAXIMIZE;

};

class Function;
class Panel;
class Container : public Component
{
protected:
  static void closeCallback(Widget widget, XtPointer client_data, XtPointer call_data);
  static void eventCallback(Widget widget, XtPointer client_data, XEvent* event, Boolean* unused);

  Atom deleteWindowAtom;
  int lastWidth;
  int lastHeight;
  std::auto_ptr<Panel> contentPanel;
  std::auto_ptr<Function> closeFunction;
  std::auto_ptr<Function> showFunction;
  std::auto_ptr<Function> resizeFunction;
  std::auto_ptr<Function> minimizeFunction;
  std::auto_ptr<Function> moveFunction;
  std::auto_ptr<Function> focusFunction;
  std::auto_ptr<Function> unfocusFunction;


public:
  Container(std::string name);
  virtual ~Container();

  virtual Panel* getContentPanel();
  virtual void setDecorations(int decorations);
  virtual void setStyle(int style);
  virtual void setVisible(bool visible);
  virtual void setInitialFocus(Component* component);
  virtual void setResizable(bool resizable);
  virtual void setMovable(bool movable);
  virtual void setMwmFunctions(int functions);
  virtual void unmap();
  virtual void minimize();

  virtual void setCloseFunction(Function* function);
  virtual void setShowFunction(Function* function);
  virtual void setMoveFunction(Function* function);
  virtual void setResizeFunction(Function* function);
  virtual void setMinimizeFunction(Function* function);
  virtual void setFocusFunction(Function* function);
  virtual void setUnfocusFunction(Function* function);

};

}

#endif

