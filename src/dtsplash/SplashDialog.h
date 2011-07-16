#ifndef SPLASHDIALOG_H
#define SPLASHDIALOG_H

#include <motifmm.h>

class SplashDialog : public Motif::Dialog
{
private:
  /** Default length of time to display the splash screen (seconds.) */
  static const int DEFAULT_SPLASH_TIME = 3;
  std::auto_ptr<Motif::Panel> vendorLogoPanel;
  std::auto_ptr<Motif::Label> vendorLogoLabel;
  std::auto_ptr<Motif::Timer> timer;
  void init(unsigned int seconds);

public:
  SplashDialog();
  SplashDialog(unsigned int seconds);
  ~SplashDialog();

  void onTimerTick(void* caller);

};

#endif

