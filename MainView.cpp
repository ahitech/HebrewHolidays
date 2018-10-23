#include <InterfaceDefs.h>
#include <LayoutBuilder.h>

#include "MainView.h"

MainView::MainView (BRect frame)
	: BView(frame,
			"MainView",
			B_FOLLOW_ALL_SIDES,
			B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS | B_PULSE_NEEDED),
	  dateView (NULL)
{
	float width, height;
	dateView = new DateView();

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	dateView->UpdateDay();

	moonView = new MoonPhaseDisplay();

	BLayoutBuilder::Group<>(this, B_VERTICAL, TEXT_MARGINS)
		.SetExplicitAlignment(BAlignment(B_ALIGN_USE_FULL_WIDTH,
										 B_ALIGN_USE_FULL_HEIGHT))
		.SetExplicitMinSize(BSize(120, 125))
		.Add(dateView, 0.0f)
		.Add(moonView, 1.0f)
			.SetExplicitMinSize (BSize (100, 100))
			.SetExplicitAlignment(BAlignment (B_ALIGN_HORIZONTAL_CENTER,
											  B_ALIGN_TOP))
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
			*height += tempHeight + TEXT_MARGINS;
			temp = temp->NextSibling();
		}
	}
}


void MainView::Pulse ()
{
	if (dateView)
	{
		dateView->UpdateDay();
	}
}


#if 0
void MainView::ResizeTo (float width, float height)
{
}


void MainView::ResizeBy (float width, float height)
{
	BRect bounds = this->Bounds();
	this->ResizeTo (bounds.Width() + width, bounds.Height() + height);
}
#endif
