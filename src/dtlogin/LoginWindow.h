#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <motifmm.h>

class LoginWindow : public Motif::Window
{
private:
  std::auto_ptr<Motif::Panel> containerPanel;
  std::auto_ptr<Motif::Panel> passwordPanel;
  std::auto_ptr<Motif::Password> password;
  std::auto_ptr<Motif::Text> text;
  std::auto_ptr<Motif::Button> okButton;
  std::auto_ptr<Motif::Button> startOverButton;
  std::auto_ptr<Motif::Button> shutdownButton;
  std::auto_ptr<Motif::Button> restartButton;
  std::auto_ptr<Motif::Label> informationLabel;
  std::auto_ptr<Motif::Label> userInformationLabel;

  std::auto_ptr<Motif::Panel> vendorLogoPanel;
  std::auto_ptr<Motif::Label> vendorLogoLabel;

  bool userEntry;

public:
  LoginWindow();
  ~LoginWindow();

  void onShow(void* caller);
  void onClose(void* caller);
  void onTextActivate(void* caller);
  void onPasswordActivate(void* caller);
  void onOkButtonActivate(void* caller);
  void onStartOverButtonActivate(void* caller);
  void onShutdownButtonActivate(void* caller);
  void onRestartButtonActivate(void* caller);

};

#endif

