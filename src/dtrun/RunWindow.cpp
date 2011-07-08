#include "RunWindow.h"

RunWindow::RunWindow() : Motif::Window("RunWindow")
{
  setTitle("Run");
  setWidth(320);
  setHeight(50);
  setCloseFunction(FUNCTION(RunWindow::onClose));

  mainPanel.reset(new Motif::Panel("mainPanel", getContentPanel()));
  //mainPanel->setLeftAttachment(Motif::Attachment::FORM);
  //mainPanel->setRightAttachment(Motif::Attachment::FORM);
  //mainPanel->setTopAttachment(Motif::Attachment::WIDGET);
  //mainPanel->setBottomAttachment(Motif::Attachment::WIDGET);
  mainPanel->setLeftOffset(0);
  mainPanel->setRightOffset(0);
  mainPanel->setShadowThickness(1);


  pathText.reset(new Motif::Text("pathText", mainPanel.get()));
  //pathText->set

  setNoResize(true);
  setVisible(true);
}

RunWindow::~RunWindow()
{

}

void RunWindow::onClose(void* caller)
{
  exit(0);
}

