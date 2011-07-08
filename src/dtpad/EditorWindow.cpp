#include "EditorWindow.h"

EditorWindow::EditorWindow() : Motif::Window("editorWindow")
{
  setTitle("Text Editor - (UNTITLED)");
  setWidth(320);
  setHeight(240);
  setCloseFunction(FUNCTION(EditorWindow::onClose));

  menuBar.reset(new Motif::MenuBar("menuBar", getContentPanel()));
  menuBar->setLeftAttachment(Motif::Attachment::FORM);
  menuBar->setRightAttachment(Motif::Attachment::FORM);
  menuBar->setTopAttachment(Motif::Attachment::FORM);
  filePulldownMenu.reset(new Motif::PulldownMenu("filePulldownMenu", menuBar.get()));
  filePulldownMenu->setText("File");
  closeButton.reset(new Motif::Button("closeButton", filePulldownMenu.get()));
  closeButton->setText("Close");
  closeButton->setSensitive(false);
  editPulldownMenu.reset(new Motif::PulldownMenu("editPulldownMenu", menuBar.get()));
  editPulldownMenu->setText("Edit");
  optionsPulldownMenu.reset(new Motif::PulldownMenu("optionsPulldownMenu", menuBar.get()));
  optionsPulldownMenu->setText("Options");
  helpPulldownMenu.reset(new Motif::PulldownMenu("helpPulldownMenu", menuBar.get()));
  helpPulldownMenu->setText("Help");
  menuBar->setHelpMenu(helpPulldownMenu.get());

  statusPanel.reset(new Motif::Panel("statusPanel", getContentPanel()));
  statusPanel->setLeftAttachment(Motif::Attachment::FORM);
  statusPanel->setRightAttachment(Motif::Attachment::FORM);
  statusPanel->setBottomAttachment(Motif::Attachment::FORM);
  statusPanel->setHeight(25);
  statusPanel->setShadowThickness(1);

  mainPanel.reset(new Motif::Panel("mainPanel", getContentPanel()));
  mainPanel->setLeftAttachment(Motif::Attachment::FORM);
  mainPanel->setRightAttachment(Motif::Attachment::FORM);
  mainPanel->setTopAttachment(Motif::Attachment::WIDGET);
  mainPanel->setBottomAttachment(Motif::Attachment::WIDGET);
  mainPanel->setLeftOffset(0);
  mainPanel->setRightOffset(0);
  mainPanel->setTopWidget(menuBar.get());
  mainPanel->setBottomWidget(statusPanel.get());
  mainPanel->setShadowThickness(1);

  editorPanel.reset(new Motif::Panel("editorPanel", mainPanel.get()));
  editorPanel->setLeftAttachment(Motif::Attachment::FORM);
  editorPanel->setLeftOffset(5);
  editorPanel->setRightAttachment(Motif::Attachment::FORM);
  editorPanel->setRightOffset(5);
  editorPanel->setTopAttachment(Motif::Attachment::FORM);
  editorPanel->setTopOffset(5);
  editorPanel->setBottomAttachment(Motif::Attachment::FORM);
  editorPanel->setBottomOffset(5);
  editorPanel->setShadowThickness(1);

  editorScrolledText.reset(new Motif::ScrolledText("editorScrolledText", editorPanel.get()));

  setVisible(true);
}

EditorWindow::~EditorWindow()
{

}

void EditorWindow::onClose(void* caller)
{
  exit(0);
}

