#ifndef OPENCDE_EXCEPTIONDIALOG_H
#define OPENCDE_EXCEPTIONDIALOG_H

#include <opencde.h>

namespace OpenCDE
{

class ExceptionDialog : public Motif::Dialog
{
private:
  std::auto_ptr<Motif::Label> messageLabel;
  std::auto_ptr<Motif::Label> informationLabel;
  std::auto_ptr<Motif::Label> logoLabel;
  std::auto_ptr<Motif::Panel> informationPanel;
  std::auto_ptr<Motif::Panel> scrolledTextPanel;
  std::auto_ptr<Motif::ScrolledText> informationScrolledText;
  std::auto_ptr<Motif::Button> closeButton;

public:
  ExceptionDialog(std::string message, std::string information);
  ~ExceptionDialog();

  void onClose(void* caller);
};

}

#endif

