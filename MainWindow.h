#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>

#include "MainView.h"

class MainWindow : public BWindow
{
public:
						MainWindow(void);
						~MainWindow();
			void		MessageReceived(BMessage *msg);
			bool		QuitRequested(void);

private:
	MainView* mainView;
};

#endif
