#include "MainView.h"

MainView::MainView (BRect frame)
	: BView(frame,
			"MainView",
			B_FOLLOW_H_CENTER | B_FOLLOW_TOP,
			B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS),
	  dateView (NULL)
{
	float width, height;
	dateView = new DateView();

	dateView->UpdateDay();
	dateView->ResizeToPreferred();
	dateView->GetPreferredSize(&width, &height);
	this->AddChild (dateView);
	ResizeTo(width, height);
}


MainView::~MainView ()
{
	this->LockLooper();
	if (dateView != NULL)
	{
		dateView->RemoveSelf();
		delete dateView;
	}
//	this->UnlockLooper();
}



void MainView::GetPreferredSize (float *width, float *height)
{
	if (dateView != NULL)
	{
		dateView->GetPreferredSize(width, height);
	}
	else
	{
		*width = *height = TEXT_MARGINS;
	}
}
