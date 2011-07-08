#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <motifmm.h>
#include <opencde.h>

class PanelWindow;
class MenuWindow : public Motif::Window
{
private:
  std::vector<std::string> menuEntries;
  Motif::Button* menuButton;
  int borderHeight;
  int targetHeight;
  std::string name;
  PanelWindow* panelWindow;
  Motif::auto_vector<Motif::IconButton> entryButtons;
  std::auto_ptr<Motif::Timer> slideTimer;

public:
  MenuWindow(PanelWindow* panelWindow, Motif::Button* menuButton, std::string name);
  ~MenuWindow();

  std::string getName();
  Motif::Button* getMenuButton();
  void onClose(void* caller);
  void onShow(void* caller);
  void onEntryButtonClicked(void* caller);
  void onSlideInterval(void* caller);

};

#endif

