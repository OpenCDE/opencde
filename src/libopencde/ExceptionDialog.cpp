#include <opencde.h>

namespace OpenCDE
{

ExceptionDialog::ExceptionDialog(std::string message, std::string information) : Motif::Dialog("exceptionDialog")
{
  setTitle("OpenCDE Exception");
  setWidth(400);
  setHeight(300);
  setX((Motif::Application::getScreenWidth() / 2) - (400 / 2));
  setY((Motif::Application::getScreenHeight() / 2) - (300 / 2));
  //setDecorations(Motif::Decorations::BORDER | Motif::Decorations::TITLE | Motif::Decorations::MENU);
  setMwmFunctions(Motif::MwmFunctions::CLOSE | Motif::MwmFunctions::MOVE);
  setStyle(Motif::Style::APPLICATION);
  setCloseFunction(FUNCTION(ExceptionDialog::onClose));

  logoLabel.reset(new Motif::Label("logoLabel", getContentPanel()));
  logoLabel->setPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/OpenCDEExceptionBanner.xpm");
  logoLabel->setWidth(390);
  logoLabel->setHeight(75);
  logoLabel->setTopAttachment(Motif::Attachment::FORM);
  logoLabel->setLeftAttachment(Motif::Attachment::FORM);
  logoLabel->setLeftOffset(10);
  logoLabel->setTopOffset(10);

/*
  informationPanel.reset(new Motif::Panel("informationPanel", getContentPanel()));
  informationPanel->setShadowThickness(1);
  informationPanel->setTopAttachment(Motif::Attachment::FORM);
  informationPanel->setLeftAttachment(Motif::Attachment::FORM);
  informationPanel->setRightAttachment(Motif::Attachment::FORM);
  informationPanel->setBottomAttachment(Motif::Attachment::FORM);
  informationPanel->setTopOffset(125);
  informationPanel->setLeftOffset(5);
  informationPanel->setRightOffset(5);
  informationPanel->setBottomOffset(35);
*/

  messageLabel.reset(new Motif::Label("messageLabel", getContentPanel()));
  messageLabel->setText("Exception: " + message);
  messageLabel->setTopAttachment(Motif::Attachment::FORM);
  messageLabel->setRightAttachment(Motif::Attachment::FORM);
  messageLabel->setLeftAttachment(Motif::Attachment::FORM);
  messageLabel->setBottomAttachment(Motif::Attachment::NONE);
  messageLabel->setTopOffset(120);
  messageLabel->setLeftOffset(10);
  messageLabel->setRightOffset(10);

  informationLabel.reset(new Motif::Label("informationLabel", getContentPanel()));
  informationLabel->setText(information);
  informationLabel->setTopAttachment(Motif::Attachment::FORM);
  informationLabel->setRightAttachment(Motif::Attachment::FORM);
  informationLabel->setLeftAttachment(Motif::Attachment::FORM);
  informationLabel->setBottomAttachment(Motif::Attachment::FORM);
  informationLabel->setTopOffset(160);
  informationLabel->setRightOffset(10);
  informationLabel->setBottomOffset(75);
  informationLabel->setLeftOffset(10);

  closeButton.reset(new Motif::Button("closeButton", getContentPanel()));
  //closeButton->setShowAsDefault(1);
  closeButton->setText("Close");
  closeButton->setShadowThickness(1);
  closeButton->setHighlightThickness(1);
  closeButton->setBottomAttachment(Motif::Attachment::FORM);
  closeButton->setRightAttachment(Motif::Attachment::FORM);
  closeButton->setTopAttachment(Motif::Attachment::NONE);
  closeButton->setLeftAttachment(Motif::Attachment::NONE);
  closeButton->setRightOffset(5);
  closeButton->setBottomOffset(5);
  closeButton->setWidth(80);
  closeButton->setHeight(25);
  closeButton->setActivateFunction(FUNCTION(ExceptionDialog::onClose));

  setVisible(true);
}

ExceptionDialog::~ExceptionDialog()
{

}

void ExceptionDialog::onClose(void* caller)
{
  exit(0);
}

}
