#include "MainWindow.h"

#include <Application.h>
#include <InterfaceDefs.h>
#include <LayoutBuilder.h>

MainWindow::~MainWindow()
{
	if (NULL != mainView)
	{
		mainView->RemoveSelf();
		delete (mainView);
	}
}


MainWindow::MainWindow(void)
	:	BWindow (BRect(100,100,220,225),
				 "HH",
				 B_TITLED_WINDOW,
				 B_ASYNCHRONOUS_CONTROLS),
		mainView (NULL)
{
	float width, height;
	this->mainView = new MainView(Bounds());

	GetSizeLimits (NULL, &width, NULL, &height);
	SetSizeLimits (115, width, 125, height);

	mainView->GetPreferredSize(&width, &height);
	ResizeTo (width, height);
	AddChild (mainView);

}


void
MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}


bool
MainWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
