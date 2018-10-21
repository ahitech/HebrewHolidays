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

	moonView = new MoonPhaseDisplay(BRect(0, 20, 300, 320));

	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.SetExplicitAlignment(BAlignment(B_ALIGN_USE_FULL_WIDTH,
										 B_ALIGN_USE_FULL_HEIGHT))
		.Add(dateView, 0.0f)
		.Add(moonView, 1.0f)
	.End();

	ResizeToPreferred();
}


MainView::~MainView ()
{
	BView *temp, *tempSibling;
	this->LockLooper();

	if (temp = this->ChildAt(0))
	{
		while (temp) {
			tempSibling = temp->NextSibling();
			temp->RemoveSelf();
			temp = tempSibling;
		}
	}
/*
	if (dateView != NULL)
	{
		dateView->RemoveSelf();
		delete dateView;
	}
*/
//	this->UnlockLooper();
}



void MainView::GetPreferredSize (float *width, float *height)
{
	float tempWidth, tempHeight;
	BView* temp;

	// Sanity check
	if (width == NULL || height == NULL)
		return;

	*width = *height = TEXT_MARGINS;

	if (temp = this->ChildAt(0))
	{
		while (temp) {
			temp->GetPreferredSize(&tempWidth, &tempHeight);
			if (tempWidth > *width)
				*width = tempWidth;
			*height += tempHeight;
			temp = temp->NextSibling();
		}
	}
}



void MainView::ResizeTo (float width, float height)
{
}


void MainView::ResizeBy (float width, float height)
{
	BRect bounds = this->Bounds();
	this->ResizeTo (bounds.Width() + width, bounds.Height() + height);
}
