#ifndef SPLASHDIALOG_H
#define SPLASHDIALOG_H

#include <motifmm.h>

class SplashDialog : public Motif::Dialog
{
private:
  std::auto_ptr<Motif::Panel> vendorLogoPanel;
  std::auto_ptr<Motif::Label> vendorLogoLabel;

public:
  SplashDialog();
  ~SplashDialog();

};

#endif

