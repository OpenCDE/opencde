#include "ExitDialog.h"
#include "PanelWindow.h"

ExitDialog::ExitDialog(PanelWindow* panelWindow) : Motif::Dialog("exitDialog")
{
  this->panelWindow = panelWindow;
  setTitle("Logout Confirmation");
  setStyle(Motif::Style::SYSTEM);
  setDecorations(Motif::Decorations::TITLE | Motif::Decorations::BORDER);
  setMwmFunctions(Motif::MwmFunctions::CLOSE);
  setWidth(420);
  setHeight(210);
  setX((Motif::Application::getScreenWidth() / 2) - (420 / 2));
  setY((Motif::Application::getScreenHeight() / 2) - (210 / 2));

  buttonsPanel.reset(new Motif::Panel("buttonsPanel", getContentPanel()));
  buttonsPanel->setShadowThickness(1);
  buttonsPanel->setTopAttachment(Motif::Attachment::FORM);
  buttonsPanel->setLeftAttachment(Motif::Attachment::FORM);
  buttonsPanel->setRightAttachment(Motif::Attachment::FORM);
  buttonsPanel->setBottomAttachment(Motif::Attachment::FORM);
  buttonsPanel->setTopOffset(150);

  labelPanel.reset(new Motif::Panel("labelPanel", getContentPanel()));
  labelPanel->setShadowThickness(1);
  labelPanel->setTopAttachment(Motif::Attachment::FORM);
  labelPanel->setLeftAttachment(Motif::Attachment::FORM);
  labelPanel->setRightAttachment(Motif::Attachment::FORM);
  labelPanel->setBottomAttachment(Motif::Attachment::WIDGET);
  labelPanel->setBottomWidget(buttonsPanel.get());

  iconLabel.reset(new Motif::Label("iconLabel", labelPanel.get()));
  iconLabel->setPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fpexclamation.xpm");
  iconLabel->setBottomAttachment(Motif::Attachment::FORM);
  iconLabel->setTopOffset(10);
  iconLabel->setLeftOffset(1);
  iconLabel->setBottomOffset(10);

  exitLabel.reset(new Motif::Label("exitLabel", labelPanel.get()));
  exitLabel->setText("Exiting the desktop session...\n\nApplication updates you have not saved may be lost.\n\nContinue Logout?");
  exitLabel->setTopAttachment(Motif::Attachment::FORM);
  exitLabel->setLeftAttachment(Motif::Attachment::WIDGET);
  exitLabel->setRightAttachment(Motif::Attachment::FORM);
  exitLabel->setBottomAttachment(Motif::Attachment::FORM);
  exitLabel->setTopOffset(10);
  exitLabel->setLeftWidget(iconLabel.get());
  exitLabel->setBottomOffset(10);
  exitLabel->setRightOffset(10);

  okButton.reset(new Motif::Button("okButton", buttonsPanel.get()));
  okButton->setShadowThickness(1);
  okButton->setHighlightThickness(1);
  okButton->setShowAsDefault(1);
  okButton->setText("OK");
  okButton->setTopAttachment(Motif::Attachment::FORM);
  okButton->setLeftAttachment(Motif::Attachment::FORM);
  okButton->setLeftOffset(10);
  okButton->setTopOffset(10);
  okButton->setHeight(37);
  okButton->setWidth(70);
  okButton->setActivateFunction(FUNCTION(ExitDialog::onOkButtonClicked));

  cancelButton.reset(new Motif::Button("cancelButton", buttonsPanel.get()));
  cancelButton->setShadowThickness(1);
  cancelButton->setHighlightThickness(1);
  cancelButton->setText("Cancel");
  cancelButton->setShowAsDefault(1);
  cancelButton->setTopAttachment(Motif::Attachment::FORM);
  cancelButton->setRightAttachment(Motif::Attachment::FORM);
  cancelButton->setLeftAttachment(Motif::Attachment::NONE);
  cancelButton->setRightOffset(175);
  cancelButton->setTopOffset(10);
  cancelButton->setHeight(37);
  cancelButton->setWidth(70);
  cancelButton->setActivateFunction(FUNCTION(ExitDialog::onCancelButtonClicked));

  helpButton.reset(new Motif::Button("helpButton", buttonsPanel.get()));
  helpButton->setShadowThickness(1);
  helpButton->setHighlightThickness(1);
  helpButton->setText("Help");
  helpButton->setShowAsDefault(1);
  helpButton->setTopAttachment(Motif::Attachment::FORM);
  helpButton->setRightAttachment(Motif::Attachment::FORM);
  helpButton->setLeftAttachment(Motif::Attachment::NONE);
  helpButton->setRightOffset(10);
  helpButton->setTopOffset(10);
  helpButton->setHeight(37);
  helpButton->setWidth(70);
  helpButton->setActivateFunction(FUNCTION(ExitDialog::onHelpButtonClicked));

  setCloseFunction(FUNCTION(ExitDialog::onClose));
  setVisible(true);
}

ExitDialog::~ExitDialog()
{

}

void ExitDialog::onClose(void* caller)
{
  panelWindow->onExitDialogClose(caller);
}

void ExitDialog::onCancelButtonClicked(void* caller)
{
  onClose(caller);
}

void ExitDialog::onOkButtonClicked(void* caller)
{
  exit(0);
}

void ExitDialog::onHelpButtonClicked(void* caller)
{
  onClose(caller);
}

