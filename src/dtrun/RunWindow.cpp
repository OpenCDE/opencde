/* 
 * RunWindow.cpp
 *
 * Copyright 2011 Robert Tomsick. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright 
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright 
 *       notice, this list of conditions and the following disclaimer in the 
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY ROBERT TOMSICK ``AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN 
 * NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * Dtrun.  It runs things.  Basically the GUI equivalent of system()
 * plus a cancel button.  Not much more to say than that.
 */

#include "RunWindow.h"

#include <opencde.h>

RunWindow::RunWindow() : Motif::Window("RunWindow")
{
  this->setTitle("Run");
  this->setWidth(RunWindow::width);
  this->setHeight(RunWindow::height);
  this->setCloseFunction(FUNCTION(RunWindow::onClose));

  mainPanel.reset(new Motif::Panel("mainPanel", getContentPanel()));
  mainPanel->setLeftAttachment(Motif::Attachment::FORM);
  mainPanel->setRightAttachment(Motif::Attachment::FORM);
  mainPanel->setTopAttachment(Motif::Attachment::FORM);
  mainPanel->setBottomAttachment(Motif::Attachment::FORM);
  mainPanel->setLeftOffset(0);
  mainPanel->setRightOffset(0);
  mainPanel->setShadowThickness(1);

  /* Command input */
  pathText.reset(new Motif::Text("pathText", mainPanel.get()));
  pathText->setActivateFunction(FUNCTION(RunWindow::onRunButtonPressed));
  
  pathText->setTopAttachment(Motif::Attachment::FORM);
  pathText->setTopOffset(10);
  
  pathText->setLeftAttachment(Motif::Attachment::FORM);
  pathText->setLeftOffset(10);
  
  pathText->setRightAttachment(Motif::Attachment::WIDGET);
  pathText->setRightOffset(10);
  
  pathText->setShadowThickness(2);
  
  
  /* Run */
  runButton.reset(new Motif::Button("runButton", mainPanel.get()));
  runButton->setActivateFunction(FUNCTION(RunWindow::onRunButtonPressed));
  
  runButton->setRightAttachment(Motif::Attachment::WIDGET);
  runButton->setRightOffset(10);
  
  runButton->setTopAttachment(Motif::Attachment::FORM);
  runButton->setTopOffset(8);
  
  runButton->setText("Run");
  runButton->setShadowThickness(2);
  runButton->setShowAsDefault(1);
  
  
  /* Close */
  closeButton.reset(new Motif::Button("cancelButton", mainPanel.get()));
  closeButton->setActivateFunction(FUNCTION(RunWindow::onClose));
  
  closeButton->setRightAttachment(Motif::Attachment::FORM);
  closeButton->setRightOffset(9);
  
  closeButton->setTopAttachment(Motif::Attachment::FORM);
  closeButton->setTopOffset(14);
  
  closeButton->setText("Cancel");
  closeButton->setShadowThickness(2);
  
  /* set our widget attachment now that everything's been created */
  runButton->setRightWidget(closeButton.get());
  
  pathText->setRightWidget(runButton.get());
  
  
  this->setMwmFunctions(Motif::MwmFunctions::ALL | Motif::MwmFunctions::RESIZE | Motif::MwmFunctions::MAXIMIZE);
    
  this->setVisible(true);
  pathText->setFocus();
}

RunWindow::~RunWindow()
{

}

void RunWindow::onClose(void* caller)
{
  exit(EXIT_SUCCESS);
}


void RunWindow::onRunButtonPressed(void* caller)
{
  /* FIXME: handle exec ourselves.  Do we really want this going
   * through to system()?
   */
  
  /* since we don't want to be too careless, let's do a tiny bit of
   * sanity checking before we dump this into system()...
   */
  std::string text = pathText->getText();
  if (text.empty() || 
      std::string::npos == text.find_last_not_of(" \t\f\v\n\r"))
  {
    return;
  }
   
  OpenCDE::Shell::executeFork(this->pathText->getText());
  exit(EXIT_SUCCESS);
}
