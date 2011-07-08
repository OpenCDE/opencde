#ifndef LOCKDIALOG_H
#define LOCKDIALOG_H

#include <motifmm.h>

class LockDialog : public Motif::Dialog
{
private:
  std::auto_ptr<Motif::Panel> dialogPanel;
  std::auto_ptr<Motif::Panel> passwordPanel;
  std::auto_ptr<Motif::Password> password;
  std::auto_ptr<Motif::Panel> vendorLogoPanel;
  std::auto_ptr<Motif::Label> vendorLogoLabel;
  std::auto_ptr<Motif::Label> passwordLabel;
  std::auto_ptr<Motif::Label> userInformationLabel;
  std::auto_ptr<Motif::Label> informationLabel;

public:
  LockDialog();
  ~LockDialog();

  void onShow(void* caller);
  void onClose(void* caller);
  void onPasswordActivate(void* caller);

};

#endif

