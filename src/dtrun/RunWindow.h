#ifndef RUNWINDOW_H
#define RUNWINDOW_H

#include <motifmm.h>

class RunWindow : public Motif::Window
{
private:
  static const int width = 360;
  static const int height = 50;
  std::auto_ptr<Motif::Panel> mainPanel;
  std::auto_ptr<Motif::Text> pathText;
  std::auto_ptr<Motif::Button> runButton;
  std::auto_ptr<Motif::Button> closeButton;

public:
  RunWindow();
  ~RunWindow();

  void onClose(void* caller);
  void onRunButtonPressed(void* caller);

};

#endif

