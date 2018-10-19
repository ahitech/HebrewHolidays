#include <InterfaceDefs.h>
#include <LayoutBuilder.h>

#include "MainView.h"

MainView::MainView (BRect frame)
	: BView(frame,
			"MainView",
			B_FOLLOW_ALL_SIDES,
			B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS),
	  dateView (NULL)
{
	float width, height;
	dateView = new DateView();

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	dateView->UpdateDay();
	dateView->ResizeToPreferred();
	dateView->GetPreferredSize(&width, &height);

	moonView = new MoonPhaseDisplay(BRect(0, 0, 300, 300));

//	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
//		.SetExplicitAlignment(BAlignment(B_ALIGN_USE_FULL_WIDTH,
//										 B_ALIGN_USE_FULL_HEIGHT))
//		.Add(dateView, 0.0f)
//		.Add(moonView, 0.0f)
//	.End();

	this->AddChild (dateView);
	this->AddChild (moonView);
	ResizeTo(width, 300+height);
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
