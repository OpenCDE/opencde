#include "LoginWindow.h"

#include <pwd.h>

#ifdef PLATFORM_LINUX
  #include <shadow.h>
#endif

#include <opencde.h>

LoginWindow::LoginWindow() : Motif::Window("loginWindow")
{
  userEntry = true;
  OpenCDE::Shell::execute("xsetroot -solid Black");
  OpenCDE::Shell::execute("xsetroot -cursor_name left_ptr");

  setCloseFunction(FUNCTION(LoginWindow::onClose));
  setShowFunction(FUNCTION(LoginWindow::onShow));
  setDecorations(Motif::Decorations::NONE);
  setWidth(Motif::Application::getScreenWidth());
  setHeight(Motif::Application::getScreenHeight());
  setX(0);
  setY(0);
  //setResizable(false);
  //setMovable(false);
  getContentPanel()->setShadowThickness(0);

  containerPanel.reset(new Motif::Panel("containerPanel", getContentPanel()));
  containerPanel->setWidth(800);
  containerPanel->setHeight(294);
  containerPanel->setX((Motif::Application::getScreenWidth() / 2) - (800 / 2));
  containerPanel->setY((Motif::Application::getScreenHeight() / 2) - (294 / 2));
  containerPanel->setShadowThickness(3);

  vendorLogoPanel.reset(new Motif::Panel("vendorLogoPanel", containerPanel.get()));
  vendorLogoPanel->setY(15);
  vendorLogoPanel->setX(521);
  vendorLogoPanel->setWidth(264);
  vendorLogoPanel->setHeight(264);
  vendorLogoPanel->setShadowThickness(2);

  vendorLogoLabel.reset(new Motif::Label("vendorLogoLabel", vendorLogoPanel.get()));
  vendorLogoLabel->setPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/VendorLogo.xpm");
  vendorLogoLabel->setY(4);
  vendorLogoLabel->setX(4);
  vendorLogoLabel->setWidth(256);
  vendorLogoLabel->setHeight(256);

  passwordPanel.reset(new Motif::Panel("passwordPanel", containerPanel.get()));
  passwordPanel->setY(15);
  passwordPanel->setX(15);
  passwordPanel->setWidth(506);
  passwordPanel->setHeight(264);
  passwordPanel->setShadowThickness(2);
  passwordPanel->setResizable(false);

  userInformationLabel.reset(new Motif::Label("userInformationLabel", passwordPanel.get()));
  userInformationLabel->setText("Welcome to " + OpenCDE::Environment::getHostname());
  userInformationLabel->setLeftAttachment(Motif::Attachment::FORM);
  userInformationLabel->setRightAttachment(Motif::Attachment::FORM);
  userInformationLabel->setY(50);
  userInformationLabel->setLeftOffset(25);
  userInformationLabel->setRightOffset(25);

  informationLabel.reset(new Motif::Label("informationLabel", passwordPanel.get()));
  informationLabel->setText("Please enter your user name");
  informationLabel->setLeftAttachment(Motif::Attachment::FORM);
  informationLabel->setRightAttachment(Motif::Attachment::FORM);
  informationLabel->setLeftOffset(25);
  informationLabel->setRightOffset(25);
  informationLabel->setY(125);

  text.reset(new Motif::Text("usernameText", passwordPanel.get()));
  text->setLeftAttachment(Motif::Attachment::FORM);
  text->setRightAttachment(Motif::Attachment::FORM);
  text->setLeftOffset(150);
  text->setRightOffset(150);
  text->setY(150);
  text->setActivateFunction(FUNCTION(LoginWindow::onTextActivate));
  text->setShadowThickness(1);
  text->setHighlightThickness(1);

  password.reset(new Motif::Password("password", passwordPanel.get()));
  password->setLeftAttachment(Motif::Attachment::FORM);
  password->setRightAttachment(Motif::Attachment::FORM);
  password->setLeftOffset(150);
  password->setRightOffset(150);
  password->setY(150);
  password->setActivateFunction(FUNCTION(LoginWindow::onPasswordActivate));
  password->setShadowThickness(1);
  password->setHighlightThickness(1);
  password->setVisible(false);

  okButton.reset(new Motif::Button("okButton", passwordPanel.get()));
  okButton->setShadowThickness(1);
  okButton->setBottomAttachment(Motif::Attachment::FORM);
  okButton->setBottomOffset(10);
  okButton->setText("OK");
  okButton->setX(10);
  okButton->setHeight(30);
  okButton->setWidth(100);
  okButton->setShowAsDefault(1);
  okButton->setActivateFunction(FUNCTION(LoginWindow::onOkButtonActivate));

  startOverButton.reset(new Motif::Button("startOverButton", passwordPanel.get()));
  startOverButton->setShadowThickness(1);
  startOverButton->setBottomAttachment(Motif::Attachment::FORM);
  startOverButton->setBottomOffset(10);
  startOverButton->setText("Start Over");
  startOverButton->setX(120);
  startOverButton->setHeight(30);
  startOverButton->setWidth(100);
  startOverButton->setShowAsDefault(1);
  startOverButton->setActivateFunction(FUNCTION(LoginWindow::onStartOverButtonActivate));

  shutdownButton.reset(new Motif::Button("startOverButton", passwordPanel.get()));
  shutdownButton->setShadowThickness(1);
  shutdownButton->setBottomAttachment(Motif::Attachment::FORM);
  shutdownButton->setBottomAttachment(Motif::Attachment::FORM);
  shutdownButton->setRightAttachment(Motif::Attachment::FORM);
  shutdownButton->setBottomOffset(10);
  shutdownButton->setText("Shutdown");
  shutdownButton->setRightOffset(10);
  shutdownButton->setHeight(30);
  shutdownButton->setWidth(100);
  shutdownButton->setShowAsDefault(1);
  shutdownButton->setActivateFunction(FUNCTION(LoginWindow::onShutdownButtonActivate));

  restartButton.reset(new Motif::Button("startOverButton", passwordPanel.get()));
  restartButton->setShadowThickness(1);
  restartButton->setBottomAttachment(Motif::Attachment::FORM);
  restartButton->setRightAttachment(Motif::Attachment::FORM);
  restartButton->setBottomOffset(10);
  restartButton->setText("Restart");
  restartButton->setRightOffset(120);
  restartButton->setHeight(30);
  restartButton->setWidth(100);
  restartButton->setShowAsDefault(1);
  restartButton->setActivateFunction(FUNCTION(LoginWindow::onRestartButtonActivate));

  setVisible(true);
  text->setFocus();
}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::onShow(void* caller)
{

}

void LoginWindow::onStartOverButtonActivate(void* caller)
{
  userEntry = true;
  informationLabel->setText("Please enter your user name");
  password->setText("");
  text->setText("");
  password->setVisible(false);
  text->setVisible(true);
  text->setFocus();
}

void LoginWindow::onOkButtonActivate(void* caller)
{
  if(userEntry == true)
  {
    onTextActivate(caller);
  }
  else
  {
    onPasswordActivate(caller);
  }
}

void LoginWindow::onTextActivate(void* caller)
{
  userEntry = false;
  text->setVisible(false);
  password->setVisible(true);
  password->setFocus();
  informationLabel->setText("Please enter your password");
}

void LoginWindow::onRestartButtonActivate(void* caller)
{
  OpenCDE::Shell::executeFork("shutdown -r now; reboot");

  setVisible(false);
}

void LoginWindow::onShutdownButtonActivate(void* caller)
{
  OpenCDE::Shell::executeFork("shutdown -hp now; shutdown -p now; poweroff");

  setVisible(false);
}

void LoginWindow::onPasswordActivate(void* caller)
{
  bool auth = false;
  std::string username;
  struct passwd* pass = NULL;
  char* encryptedPassword = NULL;

  userEntry = true;
  username = text->getText();
  pass = getpwnam(username.c_str());

  if(pass == NULL)
  {
    password->setText("");
    onStartOverButtonActivate(caller);
    return;
  }

#ifdef PLATFORM_LINUX

  spwd = getspnam(username.c_str());

  if (spwd != NULL)
  {
    pass->pw_passwd = spwd->sp_pwdp;
  }

#endif

  encryptedPassword = crypt(password->getText().c_str(), pass->pw_passwd);

  if(strcmp(pass->pw_passwd, encryptedPassword) == 0)
  {
    auth = true;
  }
  else
  {

  }

  password->setText("");
  text->setText("");
  password->setVisible(false);
  text->setVisible(true);
  informationLabel->setText("Please enter your user name");
  text->setFocus();

  if(auth == true)
  {
    setVisible(false);
    OpenCDE::Shell::executeFork(OpenCDE::Environment::getPrefix() + "/share/opencde/dtlogin/scripts/login " + username);
  }
}

void LoginWindow::onClose(void* caller)
{
  exit(0);
}

