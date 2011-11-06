#include "PanelWindow.h"
#include "Grab.h"
#include "MenuWindow.h"

PanelWindow::PanelWindow() : Motif::Window("panelWindow")
{
  clockPixmap = NULL;
  setIconPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/SDtWsm.l.pm");
  clockButtonIndex = -1;
  calButtonIndex = -1;
  hasDesktopsPanel = false;
  std::vector<std::string> sectionNames;
  ini.reset(new OpenCDE::Ini(OpenCDE::Environment::getHome() + "/.opencde/" + OpenCDE::Environment::getName() + "/menus.ini"));

  int currentWidth = 0;

  setDecorations(Motif::Decorations::NONE);
  setWidth(320);
  setHeight(240);
  setShowFunction(FUNCTION(PanelWindow::onShown));
  setCloseFunction(FUNCTION(PanelWindow::onClose));
  setFocusFunction(FUNCTION(PanelWindow::onFocus));
  setUnfocusFunction(FUNCTION(PanelWindow::onUnfocus));

  getContentPanel()->setShadowThickness(2);

  menusPanel.reset(new Motif::Panel("menusPanel", getContentPanel()));
  menusPanel->setShadowThickness(1);
  menusPanel->setTopAttachment(Motif::Attachment::FORM);
  menusPanel->setBottomAttachment(Motif::Attachment::FORM);
  menusPanel->setLeftAttachment(Motif::Attachment::FORM);
  menusPanel->setRightAttachment(Motif::Attachment::FORM);
  menusPanel->setTopOffset(4);
  menusPanel->setBottomOffset(4);
  menusPanel->setLeftOffset(4);
  menusPanel->setRightOffset(4);

  desktopsPanel.reset(new Motif::Panel("desktopsPanel", menusPanel.get()));

  iconsPanel.reset(new Motif::Panel("menusPanel", menusPanel.get()));
  iconsPanel->setShadowThickness(1);
  iconsPanel->setTopAttachment(Motif::Attachment::FORM);
  iconsPanel->setBottomAttachment(Motif::Attachment::FORM);
  iconsPanel->setLeftAttachment(Motif::Attachment::FORM);
  iconsPanel->setRightAttachment(Motif::Attachment::FORM);
  iconsPanel->setTopOffset(16);
  iconsPanel->setBottomOffset(1);
  iconsPanel->setLeftOffset(22);
  iconsPanel->setRightOffset(22);

  leftGrab.reset(new Grab("leftGrab", menusPanel.get(), this));
  leftGrab->setTopAttachment(Motif::Attachment::FORM);
  leftGrab->setBottomAttachment(Motif::Attachment::FORM);
  leftGrab->setTopOffset(1);
  leftGrab->setBottomOffset(1);
  leftGrab->setX(1);
  leftGrab->setWidth(21);
  leftGrab->setHeight(21);
  currentWidth += 22; // Drag handle // 325 75

  ini->getGroupNames(&menuEntries);

  for(unsigned int entryIndex = 0; entryIndex < menuEntries.size(); entryIndex++)
  {
    if(menuEntries.at(entryIndex) == "")
    {
      continue;
    }

    if(menuEntries.at(entryIndex) == "Desktops")
    {
      if(hasDesktopsPanel == true)
      {
        throw OpenCDE::OpenCDEException("You may not have more than\none desktop panel");
      }

      hasDesktopsPanel = true;
      int panelWidth = 0;
      desktopsPanel->setShadowThickness(1);
      desktopsPanel->setTopAttachment(Motif::Attachment::FORM);
      desktopsPanel->setBottomAttachment(Motif::Attachment::FORM);
      desktopsPanel->setTopOffset(1);
      desktopsPanel->setBottomOffset(1);
      desktopsPanel->setX(currentWidth);

      lockButton.reset(new Motif::Button("lockButton", desktopsPanel.get()));
      lockButton->setShadowThickness(0);
      lockButton->setHighlightThickness(1);
      lockButton->setTopAttachment(Motif::Attachment::FORM);
      lockButton->setLeftAttachment(Motif::Attachment::FORM);
      lockButton->setTopOffset(5);
      lockButton->setLeftOffset(2);
      lockButton->setLabelType(Motif::LabelType::PIXMAP);
      lockButton->setLabelPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fplock.s.xpm", true);
      lockButton->setActivateFunction(FUNCTION(PanelWindow::onLockButtonClicked));

      panelWidth+=36;

      ini->getSectionNames("Desktops", &desktopEntries);
      desktopEntries.erase(desktopEntries.begin() + 0);
      
      /* expand panel width by 130px for each button in one row of desktop
       * buttons.  (i.e. inc panel width by 
       * DESKTOP_BTN_WIDTH * (number of desktops / 2))
       */
      panelWidth += DESKTOP_BTN_WIDTH * ((desktopEntries.size() + 1) / 2);
      
      /* offset counter used to determine X coord of panels */
      unsigned int panelOffset = 0;

      for(unsigned int desktopIndex = 0; desktopIndex < desktopEntries.size(); desktopIndex++)
      {
        bool topRow = desktopIndex < (desktopEntries.size() + 1)/2;
	unsigned int panelIndex = desktopPanels.size();
	unsigned int buttonIndex = desktopButtons.size();
      
        /* first, create panels for all of the buttons */
        desktopPanels.add(new Motif::Panel("desktopPanel", desktopsPanel.get()));
        desktopPanels.at(panelIndex)->setShadowThickness(1);
        desktopPanels.at(panelIndex)->setShadowType(Motif::ShadowType::IN);
        desktopPanels.at(panelIndex)->setWidth(125);
        desktopPanels.at(panelIndex)->setHeight(28);
        
	/* bottom row panels are attached to the form, and offset, top have
	 * default attachment and have a fixed y
	 */
	if (topRow)
	{
	  desktopPanels.at(panelIndex)->setY(6);
	  panelOffset = desktopIndex;
	}
	else
	{
	  desktopPanels.at(panelIndex)->setBottomAttachment(Motif::Attachment::FORM);
	  desktopPanels.at(panelIndex)->setBottomOffset(6);
	  panelOffset = desktopIndex - ((desktopEntries.size()+1)/2);
	}
	desktopPanels.at(panelIndex)->setX(36 + (panelOffset * DESKTOP_BTN_WIDTH));
	
        /* now the buttons themselves */
        std::stringstream buttonName;
        buttonName << "desktopButton" << (1 + buttonIndex);
        desktopButtons.add(new Motif::ToggleButton(buttonName.str(), desktopPanels.at(panelIndex)));
        desktopButtons.at(buttonIndex)->setShadowThickness(2);
        desktopButtons.at(buttonIndex)->setHighlightThickness(0);
        desktopButtons.at(buttonIndex)->setTopAttachment(Motif::Attachment::FORM);
        desktopButtons.at(buttonIndex)->setLeftAttachment(Motif::Attachment::FORM);
        desktopButtons.at(buttonIndex)->setRightAttachment(Motif::Attachment::FORM);
        desktopButtons.at(buttonIndex)->setBottomAttachment(Motif::Attachment::FORM);
        desktopButtons.at(buttonIndex)->setTopOffset(1);
        desktopButtons.at(buttonIndex)->setLeftOffset(1);
        desktopButtons.at(buttonIndex)->setBottomOffset(1);
        desktopButtons.at(buttonIndex)->setRightOffset(1);
        desktopButtons.at(buttonIndex)->setText(desktopEntries.at(desktopIndex));
        desktopButtons.at(buttonIndex)->setTag(desktopEntries.at(desktopIndex));
        desktopButtons.at(buttonIndex)->setValueChangedFunction(FUNCTION(PanelWindow::onDesktopButtonClicked));
      }

      exitButton.reset(new Motif::Button("exitButton", desktopsPanel.get()));
      exitButton->setShadowThickness(0);
      exitButton->setHighlightThickness(1);
      exitButton->setBottomAttachment(Motif::Attachment::FORM);
      exitButton->setRightAttachment(Motif::Attachment::FORM);
      exitButton->setBottomOffset(5);
      exitButton->setRightOffset(2);
      exitButton->setLabelType(Motif::LabelType::PIXMAP);
      exitButton->setLabelPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fpexit.s.pm", true);
      exitButton->setActivateFunction(FUNCTION(PanelWindow::onExitButtonClicked));

      panelWidth+=31;
      desktopsPanel->setWidth(panelWidth);
      currentWidth+=panelWidth;
    }
    else
    {
      sectionNames.clear();
      ini->getSectionNames(menuEntries.at(entryIndex), &sectionNames);
      menuPanels.add(new Motif::Panel("menuPanel", menusPanel.get()));
      menuPanels.at(menuPanels.size() - 1)->setWidth(58);
      menuPanels.at(menuPanels.size() - 1)->setHeight(17);
      menuPanels.at(menuPanels.size() - 1)->setX(currentWidth);
      menuPanels.at(menuPanels.size() - 1)->setShadowThickness(1);

      menuButtons.add(new Motif::Button("menuButton", menuPanels.at(menuPanels.size() - 1)));
      menuButtons.at(menuButtons.size() - 1)->setTag(menuEntries.at(entryIndex));
      menuButtons.at(menuButtons.size() - 1)->setResizable(false);
      menuButtons.at(menuButtons.size() - 1)->setLabelType(Motif::LabelType::PIXMAP);
      menuButtons.at(menuButtons.size() - 1)->setLabelPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fpup.t.xpm");
      menuButtons.at(menuButtons.size() - 1)->setTopAttachment(Motif::Attachment::FORM);
      menuButtons.at(menuButtons.size() - 1)->setBottomAttachment(Motif::Attachment::FORM);
      menuButtons.at(menuButtons.size() - 1)->setLeftAttachment(Motif::Attachment::FORM);
      menuButtons.at(menuButtons.size() - 1)->setRightAttachment(Motif::Attachment::FORM);
      menuButtons.at(menuButtons.size() - 1)->setTopOffset(1);
      menuButtons.at(menuButtons.size() - 1)->setBottomOffset(1);
      menuButtons.at(menuButtons.size() - 1)->setLeftOffset(1);
      menuButtons.at(menuButtons.size() - 1)->setRightOffset(1);
      menuButtons.at(menuButtons.size() - 1)->setHighlightThickness(1);
      menuButtons.at(menuButtons.size() - 1)->setShadowThickness(0);
      menuButtons.at(menuButtons.size() - 1)->setArmFunction(FUNCTION(PanelWindow::onMenuButtonArmed));
      menuButtons.at(menuButtons.size() - 1)->setDisarmFunction(FUNCTION(PanelWindow::onMenuButtonDisarmed));
      menuButtons.at(menuButtons.size() - 1)->setActivateFunction(FUNCTION(PanelWindow::onMenuButtonClicked));

      if(sectionNames.size() == 1)
      {
        menuButtons.at(menuButtons.size() - 1)->setVisible(false);
      }

      iconButtons.add(new Motif::Button("iconButton", iconsPanel.get()));
      iconButtons.at(iconButtons.size() - 1)->setHighlightThickness(1);
      iconButtons.at(iconButtons.size() - 1)->setShadowThickness(0);
      iconButtons.at(iconButtons.size() - 1)->setTopAttachment(Motif::Attachment::FORM);
      iconButtons.at(iconButtons.size() - 1)->setTopOffset(1);
      //iconButtons.at(iconButtons.size() - 1)->setLabelType(Motif::LabelType::PIXMAP);
      //iconButtons.at(iconButtons.size() - 1)->setLabelPixmap(OpenCDE::Filesystem::relativeFallback(ini->getValue(menuEntries.at(entryIndex), "", "pixmap"), OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps"), true);
      iconButtons.at(iconButtons.size() - 1)->setTag(menuEntries.at(entryIndex));
      iconButtons.at(iconButtons.size() - 1)->setActivateFunction(FUNCTION(PanelWindow::onIconButtonClicked));

      if(menuEntries.at(entryIndex) == "Clock")
      {
        clockButtonIndex = iconButtons.size() - 1;
        clockTimer.reset(new Motif::Timer());
        clockTimer->start(30000);
        clockTimer->setIntervalFunction(FUNCTION(PanelWindow::onClockTimerTick));
	
	
	std::string clockPath = OpenCDE::Filesystem::pathToResource(std::string("clock.xpm"), std::string("dtpanel"), OpenCDE::Filesystem::ICON);
	iconButtons.at(clockButtonIndex)->setPixmap(clockPath);
        onClockTimerTick(NULL);
      }
      else if(menuEntries.at(entryIndex) == "Calendar")
      {
        calButtonIndex = iconButtons.size() - 1;
        calTimer.reset(new Motif::Timer());
        calTimer->start(30000);
        calTimer->setIntervalFunction(FUNCTION(PanelWindow::onCalTimerTick));
        onCalTimerTick(NULL);
      }
      else
      {
        iconButtons.at(iconButtons.size() - 1)->setLabelType(Motif::LabelType::PIXMAP);
	std::string pixmapName = ini->getValue(menuEntries.at(entryIndex), "", "pixmap");
	std::string pixmapPath = OpenCDE::Filesystem::pathToResource(pixmapName,
	  std::string("dtpanel"), OpenCDE::Filesystem::ICON);
	
	iconButtons.at(iconButtons.size() - 1)->setLabelPixmap(pixmapPath);
      }

      iconButtons.at(iconButtons.size() - 1)->setHeight(58);

      if(iconButtons.size() == 1)
      {
        iconButtons.at(iconButtons.size() - 1)->setX(currentWidth - 22 + 1);
        iconButtons.at(iconButtons.size() - 1)->setWidth(58 - 1);
      }
      else if(entryIndex == menuEntries.size() - 1)
      {
        iconButtons.at(iconButtons.size() - 1)->setX(currentWidth - 22);
        iconButtons.at(iconButtons.size() - 1)->setWidth(58 - 1);
      }
      else
      {
        iconButtons.at(iconButtons.size() - 1)->setX(currentWidth - 22);
        iconButtons.at(iconButtons.size() - 1)->setWidth(58);
      }

      currentWidth+=58;
    }
  }

  minimizeButton.reset(new Motif::Button("minimizeButton", menusPanel.get()));
  minimizeButton->setShadowThickness(1);
  minimizeButton->setHighlightThickness(0);
  minimizeButton->setTopAttachment(Motif::Attachment::FORM);
  minimizeButton->setRightAttachment(Motif::Attachment::FORM);
  minimizeButton->setLeftAttachment(Motif::Attachment::NONE);
  minimizeButton->setTopOffset(1);
  minimizeButton->setRightOffset(1);
  minimizeButton->setLabelType(Motif::LabelType::PIXMAP);
  minimizeButton->setLabelPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fpmin.l.xpm", true);
  minimizeButton->setActivateFunction(FUNCTION(PanelWindow::onMinimizeButtonClicked));
  minimizeButton->setWidth(21);
  minimizeButton->setHeight(15);

  rightGrab.reset(new Grab("rightGrab", menusPanel.get(), this));
  rightGrab->setTopAttachment(Motif::Attachment::FORM);
  rightGrab->setBottomAttachment(Motif::Attachment::FORM);
  rightGrab->setTopOffset(1);
  rightGrab->setBottomOffset(1);
  rightGrab->setX(currentWidth);
  rightGrab->setWidth(21);
  rightGrab->setHeight(21);

  currentWidth += 22;

  setWidth(currentWidth+8);
  setHeight(4 + 16 + 60 + 4);
  setX((Motif::Application::getScreenWidth() / 2) - (getWidth() / 2));
  setY(Motif::Application::getScreenHeight() - getHeight());
  desktopButtons.at(0)->setToggled(true);

  if(desktopButtons.size() > 0)
  {
    OpenCDE::Workspace::setBackgroundPixmap(OpenCDE::Filesystem::relativeFallback(ini->getValue("Desktops", desktopButtons.at(0)->getTag(), "backdrop"), OpenCDE::Environment::getPrefix() + "/share/opencde/backdrops"));
    setIconName(desktopButtons.at(0)->getTag());
  }

  setVisible(true);
  //OpenCDE::Workspace::moveToWorkspace(XtWindow(getWidget()), 0);
}

PanelWindow::~PanelWindow()
{

}

void PanelWindow::onFocus(void* caller)
{
  //Motif::Color color(getBackground());
  Motif::Color color(menuButtons.at(0)->getHighlightColor());

  Colormap cmap = DefaultColormapOfScreen(XtScreen(Motif::Application::getWidget()));
  Pixel bg;
  Pixel top;
  Pixel btm;
  Pixel hig;
  XmGetColors(XtScreen(Motif::Application::getWidget()), cmap, color.getPixel(), &bg, &top, &btm, &hig);

  getContentPanel()->setBackground(color.getPixel());
  getContentPanel()->setTopShadowColor(top);
  getContentPanel()->setBottomShadowColor(btm);
}

void PanelWindow::onUnfocus(void* caller)
{
  Motif::Color color(getBackground());

  Colormap cmap = DefaultColormapOfScreen(XtScreen(Motif::Application::getWidget()));
  Pixel bg;
  Pixel top;
  Pixel btm;
  Pixel hig;
  XmGetColors(XtScreen(Motif::Application::getWidget()), cmap, color.getPixel(), &bg, &top, &btm, &hig);

  getContentPanel()->setBackground(color.getPixel());
  getContentPanel()->setTopShadowColor(top);
  getContentPanel()->setBottomShadowColor(btm);
}

void PanelWindow::onClose(void* caller)
{
  exitDialog.reset(new ExitDialog(this));
}

void PanelWindow::onMenuButtonArmed(void* caller)
{
/*
  Motif::Button* button = (Motif::Button*)caller;

  button->setLabelPixmap("share/opencde/pixmaps/Fpdown.t.xpm", true);
  button->setTopAttachment(Motif::Attachment::FORM);
  button->setBottomAttachment(Motif::Attachment::FORM);
  button->setLeftAttachment(Motif::Attachment::FORM);
  button->setRightAttachment(Motif::Attachment::FORM);
  button->setTopOffset(1);
  button->setBottomOffset(1);
  button->setLeftOffset(1);
  button->setRightOffset(1);
*/
}

void PanelWindow::onMenuButtonDisarmed(void* caller)
{
/*
  Motif::Button* button = (Motif::Button*)caller;

  button->setLabelPixmap("share/opencde/pixmaps/Fpup.t.xpm");
  button->setTopAttachment(Motif::Attachment::FORM);
  button->setBottomAttachment(Motif::Attachment::FORM);
  button->setLeftAttachment(Motif::Attachment::FORM);
  button->setRightAttachment(Motif::Attachment::FORM);
  button->setTopOffset(1);
  button->setBottomOffset(1);
  button->setLeftOffset(1);
  button->setRightOffset(1);
*/
}

void PanelWindow::onExitButtonClicked(void* caller)
{
  onClose(caller);
}

void PanelWindow::onLockButtonClicked(void* caller)
{
  OpenCDE::Shell::executeFork(OpenCDE::Environment::getPrefix() + "/bin/dtlock");
}

void PanelWindow::onExitDialogClose(void* caller)
{
  exitDialog.reset(NULL);
}

void PanelWindow::onIconButtonClicked(void* caller)
{
  Motif::Button* iconButton = (Motif::Button*)caller;

  try
  {
    OpenCDE::Shell::executeFork(ini->getValue(iconButton->getTag(), "", "command"));
  }
  catch(std::exception& e)
  {
    Motif::MessageBox::show("noCommandMessageBox", "No command has been specified for the '" + iconButton->getTag() + "' menu item.", "Dtpanel - No Command Specified", Motif::MessageBoxType::ERROR);
  }
}

void PanelWindow::onDesktopButtonClicked(void* caller)
{
  int desktop = 0;
  Motif::ToggleButton* toggleButton = (Motif::ToggleButton*)caller;

  for(int index = 0; index < desktopButtons.size(); index++)
  {
    if(desktopButtons.at(index) != toggleButton)
    {
      desktopButtons.at(index)->setToggled(false);
    }
    else
    {
      desktop = index + 1;
    }
  }

  if(toggleButton->getToggled() == false)
  {
    toggleButton->setToggled(true);
  }

  OpenCDE::Workspace::setWorkspace(desktop);
  OpenCDE::Workspace::setBackgroundPixmap(OpenCDE::Filesystem::relativeFallback(ini->getValue("Desktops", toggleButton->getTag(), "backdrop"), OpenCDE::Environment::getPrefix() + "/share/opencde/backdrops"));
  //setTitle(toggleButton->getTag());
  setIconName(toggleButton->getTag());
}

void PanelWindow::onShown(void* caller)
{
  OpenCDE::Workspace::moveToWorkspace(XtWindow(getWidget()), 0);
}

void PanelWindow::onMinimizeButtonClicked(void* caller)
{
  while(menuWindows.size() > 0)
  {
    //menuWindows.remove(0);
    menuWindows.at(0)->onClose(caller);
  }

  minimize();
}

void PanelWindow::onMenuButtonClicked(void* caller)
{
  Motif::Button* button = (Motif::Button*)caller;

  for(int index = 0; index < menuWindows.size(); index++)
  {
    if(menuWindows.at(index)->getName() == button->getTag())
    {
      menuWindows.remove(index);
      button->setLabelPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fpup.t.xpm");
      return;
    }
  }

  menuWindows.add(new MenuWindow(this, (Motif::Button*)caller, button->getTag()));
  button->setLabelPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fpdown.t.xpm");
}

void PanelWindow::onMenuWindowClose(MenuWindow* menuWindow)
{
  menuWindow->getMenuButton()->setLabelPixmap(OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps/Fpup.t.xpm");
  menuWindows.remove(menuWindow);
}

OpenCDE::Ini* PanelWindow::getIni()
{
  return ini.get();
}

void PanelWindow::onCalTimerTick(void* caller)
{
  std::string month;
  const int month_x = 20;
  const int month_y = 24;

  int width = iconButtons.at(calButtonIndex)->getWidth();
  int height = iconButtons.at(calButtonIndex)->getHeight();

  std::string day;
  int day_x = 22;
  const int day_y = 39;

  int bufsize = 5;

  // Get the month and day from time.h
  time_t rawtime;
  struct tm* timeinfo;
  char buffer[bufsize];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,bufsize,"%b",timeinfo);
  month = buffer;

  strftime(buffer,bufsize,"%d",timeinfo);
  day = buffer;

  // Center single digit days
  if(atoi(day.c_str()) < 10) {
       day_x += 3;
  }


  iconButtons.at(calButtonIndex)->setPixmap(
  	OpenCDE::Filesystem::pathToResource(std::string("cal.xpm"), 
						std::string("dtpanel"), 
						OpenCDE::Filesystem::ICON));
  iconButtons.at(calButtonIndex)->setWidth(width);
  iconButtons.at(calButtonIndex)->setHeight(height);
  iconButtons.at(calButtonIndex)->drawText(month_x, month_y, month.c_str());
  iconButtons.at(calButtonIndex)->drawText(day_x, day_y, day.c_str());
}

void PanelWindow::onClockTimerTick(void* caller)
{
  if(clockPixmap == 0)
  {
    Pixel back;
    XpmAttributes attr;
  
    XtVaGetValues(widget, XmNbackground, &back, NULL);
    XpmColorSymbol none_color = { NULL, (char*)"None", (Pixel)0 };
    none_color.pixel = back;

    attr.valuemask = XpmReturnPixels | XpmColorSymbols | XpmCloseness;
    attr.colorsymbols = &none_color;
    attr.numsymbols = 1;
    attr.closeness = 80000;
  
    std::string clockPath = OpenCDE::Filesystem::pathToResource(std::string("clock.xpm"), std::string("dtpanel"), OpenCDE::Filesystem::ICON);
    XpmReadFileToPixmap(XtDisplay(widget), DefaultRootWindow(XtDisplay(widget)), (
char*)clockPath.c_str(), &clockPixmap, NULL, &attr);
  }

  int bufsize = 5;
  int minute;
  int hour;

  int width = iconButtons.at(clockButtonIndex)->getWidth();
  int height = iconButtons.at(clockButtonIndex)->getHeight();

  int origin_x = 24;
  int origin_y = 24;

  // Angles
  double minute_a, minute_left_a, minute_right_a;
  double hour_a, hour_left_a, hour_right_a;

  // Maximum radius of arms, width is the distance from origin to the base
  // point (left or right) of the triangle.
  int minute_r = 14;
  int hour_r   = 10;
  int width_r  = 2;

  int numPoints = 4;

  XPoint leftPoint_hour,   rightPoint_hour,   apexPoint_hour;
  XPoint leftPoint_minute, rightPoint_minute, apexPoint_minute;

  XPoint hourHand[numPoints];
  XPoint minuteHand[numPoints];

  // Get the hour and minute
  time_t rawtime;
  struct tm* timeinfo;
  char buffer[bufsize];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,bufsize,"%l",timeinfo);
  hour = atoi(buffer);

  strftime(buffer,bufsize,"%M",timeinfo);
  minute = atoi(buffer);

  // Compute the angles of all three points of the triangle in radians
  // after finding the hour and minute angles
  minute_a = 6 * minute * M_PI / 180;
  hour_a   = 0.5 * (60 * hour + minute) * M_PI / 180;

  minute_left_a  = minute_a - 90; // origin to left vertex
  hour_left_a    = hour_a   - 90; // origin to left vertex
  minute_right_a = minute_a + 90; // origin to right vertex
  hour_right_a   = hour_a   + 90; // origin to right vertex

  // Find the offsets of the points in the triangle

  // Minute hand triangle
  apexPoint_minute.x  = origin_x + (minute_r * sin(minute_a));
  apexPoint_minute.y  = origin_y - (minute_r * cos(minute_a));

  leftPoint_minute.x  = origin_x + (width_r * sin(minute_left_a));
  leftPoint_minute.y  = origin_y - (width_r * cos(minute_left_a));

  rightPoint_minute.x = origin_x + (width_r * sin(minute_right_a));
  rightPoint_minute.y = origin_y - (width_r * cos(minute_right_a));

  minuteHand[0] = leftPoint_minute;
  minuteHand[1] = rightPoint_minute;
  minuteHand[2] = apexPoint_minute;
  minuteHand[3] = leftPoint_minute;

  // Hour hand triangle
  apexPoint_hour.x  = origin_x + (hour_r   * sin(hour_a));
  apexPoint_hour.y  = origin_y - (hour_r   * cos(hour_a));

  leftPoint_hour.x  = origin_x + (width_r * sin(hour_left_a));
  leftPoint_hour.y  = origin_y - (width_r * cos(hour_left_a));

  rightPoint_hour.x = origin_x + (width_r * sin(hour_right_a));
  rightPoint_hour.y = origin_y - (width_r * cos(hour_right_a));

  // Place the points in order of drawing them, return to first point.
  hourHand[0] = leftPoint_hour;
  hourHand[1] = rightPoint_hour;
  hourHand[2] = apexPoint_hour;
  hourHand[3] = leftPoint_hour;

  iconButtons.at(clockButtonIndex)->setHeight(height);
  iconButtons.at(clockButtonIndex)->setWidth(width);

  // Draw the clock hands
  Pixmap destPixmap;
  Arg args[1];
  XtSetArg(args[0], XmNlabelPixmap, &destPixmap);
  XtGetValues(iconButtons.at(clockButtonIndex)->getWidget(), args, 1);
  
  drawClockHands(hourHand,minuteHand,numPoints);
}

void PanelWindow::drawClockHands(XPoint* hour, XPoint* minute, int points)
{
  Arg args[2];
  GC gc;
  Pixmap p;
  
  XtSetArg(args[0], XmNlabelPixmap, &p);
  XtGetValues(iconButtons.at(clockButtonIndex)->getWidget(), args, 1);

  Display *display = XtDisplay(widget);
  gc = XCreateGC(display, p, NULL, 0);
  XCopyArea(XtDisplay(widget), clockPixmap, p, gc, 0, 0, iconButtons.at(clockButtonIndex)->getWidth(), iconButtons.at(clockButtonIndex)->getHeight(), 0, 0);
  XDrawLines(display, p, gc, hour,  points, CoordModeOrigin);
  XDrawLines(display, p, gc, minute,points, CoordModeOrigin);
  XFillPolygon(display, p, gc, hour,   points, Convex, CoordModeOrigin);
  XFillPolygon(display, p, gc, minute, points, Convex, CoordModeOrigin);
  //refreshPixmap();

  if(XtIsRealized(widget) == true)
  {
    XClearArea(XtDisplay(widget), XtWindow(iconButtons.at(clockButtonIndex)->getWidget()), 0, 0, 1, 1, True);
  }
}
