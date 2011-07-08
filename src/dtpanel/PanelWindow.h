#ifndef PANELWINDOW_H
#define PANELWINDOW_H

#include <motifmm.h>
#include <opencde.h>

#include "ExitDialog.h"

class MenuWindow;
class Grab;
class PanelWindow : public Motif::Window
{
private:
  std::auto_ptr<OpenCDE::Ini> ini;
  std::auto_ptr<ExitDialog> exitDialog;

  std::auto_ptr<Motif::Panel> menusPanel;
  std::auto_ptr<Motif::Panel> iconsPanel;
  std::auto_ptr<Motif::Panel> desktopsPanel;
  bool hasDesktopsPanel;

  std::vector<std::string> menuEntries;
  Motif::auto_vector<Motif::Panel> menuPanels;
  Motif::auto_vector<Motif::Button> menuButtons;
  Motif::auto_vector<Motif::Button> iconButtons;

  std::vector<std::string> desktopEntries;
  Motif::auto_vector<Motif::Panel> desktopPanels;
  Motif::auto_vector<Motif::ToggleButton> desktopButtons;
  std::auto_ptr<Motif::Button> exitButton;
  std::auto_ptr<Motif::Button> lockButton;
  std::auto_ptr<Grab> leftGrab;
  std::auto_ptr<Grab> rightGrab;
  std::auto_ptr<Motif::Button> minimizeButton;
  Motif::auto_vector<MenuWindow> menuWindows;

public:
  PanelWindow();
  ~PanelWindow();

  void onFocus(void* caller);
  void onUnfocus(void* caller);
  void onClose(void* caller);
  void onShown(void* caller);

  void onMenuButtonArmed(void* caller);
  void onMenuButtonDisarmed(void* caller);
  void onMenuButtonClicked(void* caller);
  void onLockButtonClicked(void* caller);
  void onMinimizeButtonClicked(void* caller);
  void onExitButtonClicked(void* caller);
  void onExitDialogClose(void* caller);
  void onIconButtonClicked(void* caller);
  void onDesktopButtonClicked(void* caller);
  void onMenuWindowClose(MenuWindow* menuWindow);

  OpenCDE::Ini* getIni();

};

#endif

