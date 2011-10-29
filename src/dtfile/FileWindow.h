#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <motifmm.h>
#include <opencde.h>

class FileView;
class FileWindow : public Motif::Window
{
private:
  std::auto_ptr<Motif::Panel> statusPanel;
  std::auto_ptr<Motif::Panel> mainPanel;
  std::auto_ptr<Motif::Panel> filePanel;
  std::auto_ptr<Motif::MenuBar> menuBar;

  std::auto_ptr<Motif::PulldownMenu> filePulldownMenu;
  std::auto_ptr<Motif::PulldownMenu> selectedPulldownMenu;
  std::auto_ptr<Motif::PulldownMenu> viewPulldownMenu;
  std::auto_ptr<Motif::PulldownMenu> helpPulldownMenu;
  std::auto_ptr<Motif::Button> newFolderButton;
  std::auto_ptr<Motif::Button> newFileButton;
  std::auto_ptr<Motif::Button> instanceButton;
  std::auto_ptr<Motif::Button> terminalButton;
  std::auto_ptr<Motif::Button> closeButton;
  std::auto_ptr<Motif::Button> helpButton;
  std::auto_ptr<Motif::Button> aboutButton;
  Motif::auto_vector<Motif::Separator> separators;

  std::auto_ptr<Motif::ScrollBar> fileScroll;
  std::auto_ptr<Motif::Label> statusLabel;
  std::auto_ptr<FileView> fileView;
  std::auto_ptr<OpenCDE::Ini> ini;

public:
  FileWindow(std::string path);
  ~FileWindow();

  void onClose(void* caller);
  void onScroll(void* caller);
  OpenCDE::Ini* getIni();
  void onDirectoryChanged(FileView* caller);
  void onInstanceButtonClicked(void* caller);
  void onTerminalButtonClicked(void* caller);

};

#endif

