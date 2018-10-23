#include <Application.h>
#include <File.h>
#include <Point.h>
#include <Resources.h>
#include <Roster.h>
#include <TranslationUtils.h>
#include <TranslatorFormats.h>
#include <stdio.h>


#include "MoonPhase.h"

MoonPhaseDisplay::MoonPhaseDisplay ()
	:	BView (BRect (0, 0, 100, 100),
			   "MoonPhaseDisplay",
			   B_FOLLOW_ALL_SIDES,
			   B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
		picture(NULL)
{
	// Read the picture of the moon from the resources
	app_info info;
	be_app->GetAppInfo(&info);
	BFile file(&info.ref, B_READ_ONLY);
	BResources res;
	size_t size;
	if (res.SetTo(&file) == B_OK)
	{
		picture = BTranslationUtils::GetBitmap((uint32)'PNG ', "Moon");
	}
}


MoonPhaseDisplay::~MoonPhaseDisplay ()
{
// The picture belongs to the resource file.
//	if (NULL != picture) {
//		delete picture;
//	}
}


void MoonPhaseDisplay::AttachedToWindow ()
{
	BView* parent = Parent();
	if (parent)
	{
		SetViewColor (parent->ViewColor());
	}
	BView::AttachedToWindow();
	ResizeToPreferred();
}

void MoonPhaseDisplay::Draw(BRect updateRect)
{

	BView::Draw(updateRect);
	BView::SetDrawingMode (B_OP_OVER);
	// Add it as the background of current view
	if (picture != NULL)
	{
		BRect viewBounds = Bounds(), drawTo;
		float width = viewBounds.Width(), height = viewBounds.Height();

		drawTo.SetLeftTop (BPoint (0, 0));
		if (width > height)
		{
			drawTo.SetRightBottom (BPoint (height, height));
			drawTo.OffsetBy (BPoint ((width - height)/ 2.0, 0));
		} else {
			drawTo.SetRightBottom (BPoint (width, width));
		}

		DrawBitmap (picture, drawTo);
//		printf ("In DRAW!\n");
	}
}


void MoonPhaseDisplay::GetPreferredSize (float *width, float *height)
{
	*width = *height = 100;
}

#if 0
void MoonPhaseDisplay::ResizeTo (float width, float height)
{
	if (width > height)
	{
		BView::ResizeTo (height, height);
	}
	else
	{
		BView::ResizeTo (width, width);
	}
	this->Draw (Bounds());
}

void MoonPhaseDisplay::ResizeBy (float relativeWidth, float relativeHeight)
{
	BRect rect = this->Bounds();
	this->ResizeTo (rect.Width() + relativeWidth,
					rect.Height() + relativeHeight);
}
#endif
