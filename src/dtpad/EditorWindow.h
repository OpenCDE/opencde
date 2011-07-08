#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <motifmm.h>

class EditorWindow : public Motif::Window
{
private:
  std::auto_ptr<Motif::Panel> statusPanel;
  std::auto_ptr<Motif::Panel> editorPanel;
  std::auto_ptr<Motif::Panel> mainPanel;
  std::auto_ptr<Motif::ScrolledText> editorScrolledText;
  std::auto_ptr<Motif::MenuBar> menuBar;
  std::auto_ptr<Motif::PulldownMenu> filePulldownMenu;
  std::auto_ptr<Motif::PulldownMenu> editPulldownMenu;
  std::auto_ptr<Motif::PulldownMenu> optionsPulldownMenu;
  std::auto_ptr<Motif::PulldownMenu> helpPulldownMenu;
  std::auto_ptr<Motif::Button> closeButton;

public:
  EditorWindow();
  ~EditorWindow();

  void onClose(void* caller);

};

#endif

