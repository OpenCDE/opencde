#include "SplashDialog.h"

#include <opencde.h>

SplashDialog::SplashDialog() : Motif::Dialog("splashDialog")
{
  setStyle(Motif::Style::SYSTEM);
  setDecorations(Motif::Decorations::NONE);
  setWidth(Motif::Application::getScreenWidth());
  setHeight(Motif::Application::getScreenHeight());
  setX(0);
  setY(0);
  //setResizable(false);
  setMovable(false);
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

  setVisible(true);
}

SplashDialog::~SplashDialog()
{

}
