#include <stdio.h>
#include <time.h>
#include <Window.h>

#include "DateView.h"

DateView::DateView ()
	:	BStringView (BRect(0, 0, 30, 30),
					 "Current Day", "",
					 B_FOLLOW_H_CENTER | B_FOLLOW_TOP,
					 B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE)
{
}


DateView::~DateView()
{
}


void DateView::UpdateDay(hdate_struct* currentDay)
{
	char text[100];
	BWindow* parent;

	// Lock the window while changing stuff
	if (NULL != (parent = this->Window()))
	{
		parent->LockLooper();
	}
	sprintf (text, "%s", hdate_get_format_date (currentDay, 1, 1));
	this->SetText(text);
	this->SetAlignment(B_ALIGN_CENTER);

	if (NULL != parent)
	{
		parent->UnlockLooper();
	}
}


void DateView::GetPreferredSize (float *width, float* height)
{
	const char* text = this->Text();
	struct font_height fontHeight;
	*width = TEXT_MARGINS + this->StringWidth(text);

	this->GetFontHeight(&fontHeight);
	*height = fontHeight.ascent + fontHeight.descent + fontHeight.leading;
}

void DateView::AttachedToWindow ()
{
	BView* parent = Parent();
	if (parent)
	{
		SetViewColor (parent->ViewColor());
	}
	BView::AttachedToWindow();
}
