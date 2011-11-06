#include "LockDialog.h"

#include <pwd.h>

#ifdef PLATFORM_LINUX
  #include <shadow.h>
#endif

#include <opencde.h>

LockDialog::LockDialog() : Motif::Dialog("lockDialog")
{
  int totalWidth = Motif::Application::getScreenWidth();
  int totalHeight = Motif::Application::getScreenHeight();
  int panelWidth = 640;
  int panelHeight = 294;
  int pictureSize = 256;

  //if(OpenCDE::Environment::getUsername() != "root")
  if(geteuid() != 0)
  {
    throw OpenCDE::OpenCDEException("This application must be run as root");
  }

  setCloseFunction(FUNCTION(LockDialog::onClose));
  setShowFunction(FUNCTION(LockDialog::onShow));
  setStyle(Motif::Style::SYSTEM);
  setDecorations(Motif::Decorations::NONE);
  setWidth(totalWidth);
  setHeight(totalHeight);
  setX(-1);
  setY(-1);
  //setResizable(false);
  //setMovable(false);
  setMwmFunctions(0);
  getContentPanel()->setShadowThickness(0);

  dialogPanel.reset(new Motif::Panel("dialogPanel", getContentPanel()));
  dialogPanel->setTopAttachment(Motif::Attachment::FORM);
  dialogPanel->setLeftAttachment(Motif::Attachment::FORM);
  dialogPanel->setRightAttachment(Motif::Attachment::FORM);
  dialogPanel->setBottomAttachment(Motif::Attachment::FORM);
  dialogPanel->setLeftOffset((totalWidth - panelWidth)/2);
  dialogPanel->setRightOffset((totalWidth - panelWidth)/2);
  dialogPanel->setBottomOffset((totalHeight - panelHeight)/2);
  dialogPanel->setTopOffset((totalHeight - panelHeight)/2);
  dialogPanel->setShadowThickness(3);

  vendorLogoPanel.reset(new Motif::Panel("vendorLogoPanel", dialogPanel.get()));
  vendorLogoPanel->setTopAttachment(Motif::Attachment::FORM);
  vendorLogoPanel->setRightAttachment(Motif::Attachment::FORM);
  vendorLogoPanel->setBottomAttachment(Motif::Attachment::FORM);
  vendorLogoPanel->setLeftAttachment(Motif::Attachment::FORM);
  vendorLogoPanel->setTopOffset(15);
  vendorLogoPanel->setLeftOffset(panelWidth - pictureSize - 23);
  vendorLogoPanel->setRightOffset(15);
  vendorLogoPanel->setBottomOffset(15);
  vendorLogoPanel->setShadowThickness(2);

  vendorLogoLabel.reset(new Motif::Label("vendorLogoLabel", vendorLogoPanel.get()));
  vendorLogoLabel->setPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/VendorLogo.xpm");
  vendorLogoLabel->setTopAttachment(Motif::Attachment::FORM);
  vendorLogoLabel->setBottomAttachment(Motif::Attachment::FORM);
  vendorLogoLabel->setLeftAttachment(Motif::Attachment::FORM);
  vendorLogoLabel->setRightAttachment(Motif::Attachment::FORM);
  vendorLogoLabel->setTopOffset(2);
  vendorLogoLabel->setLeftOffset(2);
  vendorLogoLabel->setRightOffset(2);
  vendorLogoLabel->setBottomOffset(2);

  passwordPanel.reset(new Motif::Panel("passwordPanel", dialogPanel.get()));
  passwordPanel->setTopAttachment(Motif::Attachment::FORM);
  passwordPanel->setLeftAttachment(Motif::Attachment::FORM);
  passwordPanel->setRightAttachment(Motif::Attachment::FORM);
  passwordPanel->setBottomAttachment(Motif::Attachment::FORM);
  passwordPanel->setTopOffset(15);
  passwordPanel->setLeftOffset(15);
  passwordPanel->setRightOffset(pictureSize + 23);
  passwordPanel->setBottomOffset(15);
  passwordPanel->setShadowThickness(2);

  userInformationLabel.reset(new Motif::Label("userInformationLabel", passwordPanel.get()));
  userInformationLabel->setText("Display locked by user " + OpenCDE::Environment::getVariable("USER") + ".");
  userInformationLabel->setTopAttachment(Motif::Attachment::FORM);
  userInformationLabel->setLeftAttachment(Motif::Attachment::FORM);
  userInformationLabel->setRightAttachment(Motif::Attachment::FORM);
  userInformationLabel->setTopOffset(75);
  userInformationLabel->setLeftOffset(25);
  userInformationLabel->setRightOffset(25);

  informationLabel.reset(new Motif::Label("informationLabel", passwordPanel.get()));
  informationLabel->setText("Enter password to unlock.");
  informationLabel->setTopAttachment(Motif::Attachment::FORM);
  informationLabel->setLeftAttachment(Motif::Attachment::FORM);
  informationLabel->setRightAttachment(Motif::Attachment::FORM);
  informationLabel->setTopOffset(100);
  informationLabel->setLeftOffset(25);
  informationLabel->setRightOffset(25);

  password.reset(new Motif::Password("password", passwordPanel.get()));
  password->setTopAttachment(Motif::Attachment::FORM);
  password->setLeftAttachment(Motif::Attachment::FORM);
  password->setRightAttachment(Motif::Attachment::FORM);
  password->setTopOffset(150);
  password->setLeftOffset(125);
  password->setRightOffset(75);
  password->setActivateFunction(FUNCTION(LockDialog::onPasswordActivate));
  password->setShadowThickness(1);
  password->setHighlightThickness(1);

  passwordLabel.reset(new Motif::Label("passwordLabel", passwordPanel.get()));
  passwordLabel->setHeight(password->getHeight());
  passwordLabel->setNoResize(true);
  passwordLabel->setText("Password:");
  passwordLabel->setTopAttachment(Motif::Attachment::FORM);
  passwordLabel->setLeftAttachment(Motif::Attachment::FORM);
  passwordLabel->setRightAttachment(Motif::Attachment::FORM);
  passwordLabel->setTopOffset(150);
  passwordLabel->setLeftOffset(40);
  passwordLabel->setRightOffset(225);

  setVisible(true);
}

LockDialog::~LockDialog()
{

}

void LockDialog::onShow(void* caller)
{

}

void LockDialog::onPasswordActivate(void* caller)
{
  struct passwd* pass = NULL;
  char* encryptedPassword = NULL;

  pass = getpwnam(OpenCDE::Environment::getVariable("USER").c_str());

  if(pass == NULL)
  {
    password->setText("");
    return;
  }

#ifdef PLATFORM_LINUX

  spwd = getspnam(OpenCDE::Environment::getVariable("USER").c_str());

  if (spwd != NULL)
  {
    pass->pw_passwd = spwd->sp_pwdp;
  }

#endif

  encryptedPassword = crypt(password->getText().c_str(), pass->pw_passwd);

  if(strcmp(pass->pw_passwd, encryptedPassword) == 0)
  {
    exit(0);
  }

  password->setText("");
}

void LockDialog::onClose(void* caller)
{
  exit(0);
}

