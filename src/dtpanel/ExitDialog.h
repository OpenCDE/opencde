#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <motifmm.h>
#include <opencde.h>

class PanelWindow;
class ExitDialog : public Motif::Dialog
{
private:
  PanelWindow* panelWindow;
  std::auto_ptr<Motif::Panel> labelPanel;
  std::auto_ptr<Motif::Panel> buttonsPanel;
  std::auto_ptr<Motif::Label> iconLabel;
  std::auto_ptr<Motif::Label> exitLabel;
  std::auto_ptr<Motif::Button> okButton;
  std::auto_ptr<Motif::Button> cancelButton;
  std::auto_ptr<Motif::Button> helpButton;

public:
  ExitDialog(PanelWindow* panelWindow);
  ~ExitDialog();

  void onClose(void* caller);
  void onOkButtonClicked(void* caller);
  void onCancelButtonClicked(void* caller);
  void onHelpButtonClicked(void* caller);
};

#endif

