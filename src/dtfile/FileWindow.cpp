#include <opencde.h>

#include "FileWindow.h"
#include "FileView.h"

FileWindow::FileWindow(std::string path) : Motif::Window("fileWindow")
{
  ini.reset(new OpenCDE::Ini(OpenCDE::Environment::getHome() + "/.opencde/dtfile/filetypes.ini"));
  setTitle("File Manager - /some/path");
  setIconName("path");
  setIconPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fphome.l.pm");
  setWidth(450);
  setHeight(350);
  setCloseFunction(FUNCTION(FileWindow::onClose));

  menuBar.reset(new Motif::MenuBar("menuBar", getContentPanel()));
  menuBar->setLeftAttachment(Motif::Attachment::FORM);
  menuBar->setRightAttachment(Motif::Attachment::FORM);
  menuBar->setTopAttachment(Motif::Attachment::FORM);
  filePulldownMenu.reset(new Motif::PulldownMenu("filePulldownMenu", menuBar.get()));
  filePulldownMenu->setText("File");
  newFolderButton.reset(new Motif::Button("newFolderButton", filePulldownMenu.get()));
  newFolderButton->setText("New Folder");
  newFileButton.reset(new Motif::Button("newFileButton", filePulldownMenu.get()));
  newFileButton->setText("New File");
  separators.add(new Motif::Separator("separator", filePulldownMenu.get()));
  instanceButton.reset(new Motif::Button("instanceButton", filePulldownMenu.get()));
  instanceButton->setText("New Window");
  instanceButton->setAccelerator("Ctrl<Key>w");
  instanceButton->setAcceleratorText("Ctrl+W");
  instanceButton->setActivateFunction(FUNCTION(FileWindow::onInstanceButtonClicked));
  terminalButton.reset(new Motif::Button("terminalButton", filePulldownMenu.get()));
  terminalButton->setText("Open Terminal");
  terminalButton->setAccelerator("Ctrl<Key>t");
  terminalButton->setAcceleratorText("Ctrl+T");
  terminalButton->setActivateFunction(FUNCTION(FileWindow::onTerminalButtonClicked));
  separators.add(new Motif::Separator("separator", filePulldownMenu.get()));
  closeButton.reset(new Motif::Button("closeButton", filePulldownMenu.get()));
  closeButton->setText("Close");
  closeButton->setActivateFunction(FUNCTION(FileWindow::onClose));
  //closeButton->setAccelerator("Alt<Key>f4");
  closeButton->setAcceleratorText("Alt+F4");
  //closeButton->setSensitive(false);
  selectedPulldownMenu.reset(new Motif::PulldownMenu("editPulldownMenu", menuBar.get()));
  selectedPulldownMenu->setText("Selected");
  viewPulldownMenu.reset(new Motif::PulldownMenu("optionsPulldownMenu", menuBar.get()));
  viewPulldownMenu->setText("View");
  helpPulldownMenu.reset(new Motif::PulldownMenu("helpPulldownMenu", menuBar.get()));
  helpPulldownMenu->setText("Help");
  menuBar->setHelpMenu(helpPulldownMenu.get());
  helpButton.reset(new Motif::Button("helpButton", helpPulldownMenu.get()));
  helpButton->setText("File Manager Help");
  //helpButton->setActivateFunction(FUNCTION(FileWindow::onClose));
  separators.add(new Motif::Separator("separator", helpPulldownMenu.get()));
  aboutButton.reset(new Motif::Button("aboutButton", helpPulldownMenu.get()));
  aboutButton->setText("About File Manager");
  //aboutButton->setActivateFunction(FUNCTION(FileWindow::onClose));

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

  filePanel.reset(new Motif::Panel("filePanel", mainPanel.get()));
  filePanel->setLeftAttachment(Motif::Attachment::FORM);
  filePanel->setLeftOffset(5);
  filePanel->setRightAttachment(Motif::Attachment::FORM);
  filePanel->setRightOffset(25);
  filePanel->setTopAttachment(Motif::Attachment::FORM);
  filePanel->setTopOffset(5);
  filePanel->setBottomAttachment(Motif::Attachment::FORM);
  filePanel->setBottomOffset(5);
  filePanel->setShadowThickness(2);
  filePanel->setShadowType(Motif::ShadowType::IN);

  statusLabel.reset(new Motif::Label("statusLabel", statusPanel.get()));
  statusLabel->setTopAttachment(Motif::Attachment::FORM);
  statusLabel->setTopOffset(1);
  statusLabel->setBottomAttachment(Motif::Attachment::FORM);
  statusLabel->setBottomOffset(1);
  statusLabel->setLeftAttachment(Motif::Attachment::FORM);
  statusLabel->setLeftOffset(1);
  statusLabel->setText("99 Items 99 Hidden");

  fileScroll.reset(new Motif::ScrollBar("fileScroll", mainPanel.get()));
  fileScroll->setTopAttachment(Motif::Attachment::FORM);
  fileScroll->setTopOffset(5);
  fileScroll->setBottomAttachment(Motif::Attachment::FORM);
  fileScroll->setBottomOffset(5);
  fileScroll->setRightAttachment(Motif::Attachment::FORM);
  fileScroll->setRightOffset(5);
  fileScroll->setLeftAttachment(Motif::Attachment::NONE);
  fileScroll->setWidth(18);
  fileScroll->setMaximum(15);
  fileScroll->setDragFunction(FUNCTION(FileWindow::onScroll));
  fileScroll->setValueChangedFunction(FUNCTION(FileWindow::onScroll));

  fileView.reset(new FileView("fileView", filePanel.get(), fileScroll.get(), ini.get(), this));
  fileView->setTopAttachment(Motif::Attachment::FORM);
  fileView->setBottomAttachment(Motif::Attachment::FORM);
  fileView->setLeftAttachment(Motif::Attachment::FORM);
  fileView->setRightAttachment(Motif::Attachment::FORM);
  fileView->setTopOffset(2);
  fileView->setBottomOffset(2);
  fileView->setLeftOffset(2);
  fileView->setRightOffset(2);
  fileView->setPath(path);

  setVisible(true);
}

FileWindow::~FileWindow()
{

}

void FileWindow::onClose(void* caller)
{
  exit(0);
}

void FileWindow::onScroll(void* caller)
{
  fileView->redraw();
}

OpenCDE::Ini* FileWindow::getIni()
{
  return ini.get();
}

void FileWindow::onDirectoryChanged(FileView* caller)
{
  std::stringstream ss;
  std::string newPath;

  newPath = caller->getPath();
  setTitle("File Manager - " + newPath);

  if(newPath == "/")
  {
    setIconName("/");
  }
  else
  {
    setIconName(newPath.substr(newPath.find_last_of("/")+1));
  }

  ss << caller->getItems()->size() << " Items " << caller->getHiddenCount() << " Hidden";
  statusLabel->setText(ss.str());
}

void FileWindow::onInstanceButtonClicked(void* caller)
{
  OpenCDE::Shell::executeFork(OpenCDE::Environment::getPrefix() + "/bin/" + OpenCDE::Environment::getName() + " " + fileView->getPath());
}

void FileWindow::onTerminalButtonClicked(void* caller)
{
  OpenCDE::Shell::executeFork("cd " + fileView->getPath() + " && " + OpenCDE::Environment::getPrefix() + "/bin/dtterm");
}

