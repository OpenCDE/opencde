#include "SplashDialog.h"

#include <opencde.h>

SplashDialog::SplashDialog() : Motif::Dialog("splashDialog")
{
  SplashDialog::init(DEFAULT_SPLASH_TIME);
}

SplashDialog::SplashDialog(unsigned int seconds) : Motif::Dialog("splashDialog")
{
  SplashDialog::init(seconds);
}

void SplashDialog::init(unsigned int seconds)
{
  setStyle(Motif::Style::SYSTEM);
  setDecorations(Motif::Decorations::NONE);
  setWidth(Motif::Application::getScreenWidth());
  setHeight(Motif::Application::getScreenHeight());
  setX(0);
  setY(0);
  //setResizable(false);
  //setMovable(false);
  setMwmFunctions(0);
  getContentPanel()->setShadowThickness(0);

  vendorLogoPanel.reset(new Motif::Panel("vendorLogoPanel", getContentPanel()));
  vendorLogoPanel->setTopAttachment(Motif::Attachment::FORM);
  vendorLogoPanel->setBottomAttachment(Motif::Attachment::FORM);
  vendorLogoPanel->setTopOffset((Motif::Application::getScreenHeight() / 2) - (128 / 2));
  //vendorLogoPanel->setBottomOffset((Motif::Application::getScreenHeight() / 2) + (128 / 2));
  vendorLogoPanel->setWidth(520);
  vendorLogoPanel->setShadowThickness(0);

/*
  dialogPanel->setTopAttachment(Motif::Attachment::FORM);
  dialogPanel->setLeftAttachment(Motif::Attachment::FORM);
  dialogPanel->setRightAttachment(Motif::Attachment::FORM);
  dialogPanel->setBottomAttachment(Motif::Attachment::FORM);
  dialogPanel->setLeftOffset((totalWidth - panelWidth)/2);
  dialogPanel->setRightOffset((totalWidth - panelWidth)/2);
  dialogPanel->setBottomOffset((totalHeight - panelHeight)/2);
  dialogPanel->setTopOffset((totalHeight - panelHeight)/2);
*/
  
  vendorLogoLabel.reset(new Motif::Label("vendorLogoLabel", vendorLogoPanel.get()));
  vendorLogoLabel->setPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Welcome.xpm");
  vendorLogoLabel->setY(4);
  vendorLogoLabel->setX(4);
  vendorLogoLabel->setWidth(512);
  vendorLogoLabel->setHeight(128);


  /* set up our timer to exit */
  int ms = seconds * 1000;
  timer.reset(new Motif::Timer());
  timer->setIntervalFunction(FUNCTION(SplashDialog::onTimerTick));
  timer->start(ms);

  setVisible(true);
}

SplashDialog::~SplashDialog()
{

}

void SplashDialog::onTimerTick(void* caller)
{
  exit(0);
}

