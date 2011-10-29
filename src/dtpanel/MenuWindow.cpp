#include "MenuWindow.h"
#include "PanelWindow.h"

MenuWindow::MenuWindow(PanelWindow* panelWindow, Motif::Button* menuButton, std::string name) : Motif::Window("menuWindow")
{
  setHeight(1);
  borderHeight = 0;
  this->menuButton = menuButton;
  this->name = name;
  this->panelWindow = panelWindow;
  setTitle(name);
  setDecorations(Motif::Decorations::TITLE | Motif::Decorations::MENU);
  setMwmFunctions(Motif::MwmFunctions::CLOSE | Motif::MwmFunctions::MOVE);
  setCloseFunction(FUNCTION(MenuWindow::onClose));
  setShowFunction(FUNCTION(MenuWindow::onShow));

  slideTimer.reset(new Motif::Timer());
  slideTimer->setIntervalFunction(FUNCTION(MenuWindow::onSlideInterval));

  panelWindow->getIni()->getSectionNames(name, &menuEntries);
  menuEntries.erase(menuEntries.begin() + 0);

  for(unsigned int entryIndex = 0; entryIndex < menuEntries.size(); entryIndex++)
  {
    entryButtons.add(new Motif::IconButton("entryButton", getContentPanel()));
    entryButtons.at(entryButtons.size() - 1)->setShadowThickness(0);
    entryButtons.at(entryButtons.size() - 1)->setHighlightThickness(1);
    entryButtons.at(entryButtons.size() - 1)->setIconPlacement(Motif::IconPlacement::LEFT);

    entryButtons.at(entryButtons.size() - 1)->setPixmap(OpenCDE::Filesystem::relativeFallback(panelWindow->getIni()->getValue(name, menuEntries.at(entryIndex), "pixmap"), OpenCDE::Environment::getPrefix() + "/share/opencde/pixmaps"));

    entryButtons.at(entryButtons.size() - 1)->setTag(menuEntries.at(entryIndex));
    entryButtons.at(entryButtons.size() - 1)->setText(menuEntries.at(entryIndex));
    entryButtons.at(entryButtons.size() - 1)->setLeftAttachment(Motif::Attachment::FORM);
    entryButtons.at(entryButtons.size() - 1)->setRightAttachment(Motif::Attachment::FORM);
    entryButtons.at(entryButtons.size() - 1)->setLeftOffset(6);
    entryButtons.at(entryButtons.size() - 1)->setRightOffset(6);
    entryButtons.at(entryButtons.size() - 1)->setY((entryIndex * 40) + 8);
    entryButtons.at(entryButtons.size() - 1)->setHeight(40);
    entryButtons.at(entryButtons.size() - 1)->setActivateFunction(FUNCTION(MenuWindow::onEntryButtonClicked));
  }

  setWidth(175);
  setHeight(1);

  setY(panelWindow->getY()-10);

  Position x;
  Position y;
  XtTranslateCoords(getContentPanel()->getWidget(), 0, 0, &x, &y);
  borderHeight = y;

  XtTranslateCoords(menuButton->getWidget(), 0, 0, &x, &y);
  setX(x-1);

  targetHeight = (menuEntries.size() * 40) + 16;

  setVisible(true);
}

MenuWindow::~MenuWindow()
{

}

std::string MenuWindow::getName()
{
  return name;
}

void MenuWindow::onEntryButtonClicked(void* caller)
{
  Motif::IconButton* iconButton = (Motif::IconButton*)caller;

  OpenCDE::Shell::executeFork(panelWindow->getIni()->getValue(name, iconButton->getTag(), "command"));
  onClose(caller);
}

void MenuWindow::onClose(void* caller)
{
  panelWindow->onMenuWindowClose(this);
}

void MenuWindow::onShow(void* caller)
{
  Position x;
  Position y;

  XtTranslateCoords(getContentPanel()->getWidget(), 0, 0, &x, &y);
  borderHeight = y - borderHeight;

  setY(panelWindow->getY() - borderHeight - 10 + 4);

  XtTranslateCoords(menuButton->getWidget(), 0, 0, &x, &y);
  setX(x-1);

  OpenCDE::Workspace::moveToWorkspace(XtWindow(getWidget()), 0);
  slideTimer->start(25);
}

Motif::Button* MenuWindow::getMenuButton()
{
  return menuButton;
}

void MenuWindow::onSlideInterval(void* caller)
{
  //for(int index = 0; index < 6; index++)
  while(true)
  {
    if(getHeight() >= targetHeight)
    {
      break;
    }

    setHeight(getHeight() + 4);
    setY(panelWindow->getY() - getHeight() - borderHeight + 4);
    //XSync(XtDisplay(widget), False);
    XmUpdateDisplay(widget);
  }

  if(getHeight() >= targetHeight)
  {
    //slideTimer->stop();
    setHeight(targetHeight);
    setY(panelWindow->getY() - getHeight() - borderHeight + 4);
  }

  //XFlush(XtDisplay(widget));
}
