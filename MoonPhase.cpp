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



/**
 *	\brief		This function covers part of the Moon picture if requested.
 *	\param[in]	day	Current moon day (day in the current moon month)
 *	\details	Details of the algorithm:
 *				Moon month can be either 29 or 30 days. I assume that it's
 *				always 29 days. I start from the full circle that covers the
 *				whole Moon's picture, then every day (starting with 1st)
 *				until 14th I substract a part that goes from pole to pole and
 * 				amounts to 1/14 of Moon's picture width at the widest point,
 *				namely, the equator. The 15th day is always full moon (no
 *				black part at all). Then I start to add black parts of the same
 *				width on the right, and at 30th day it is full black again.
 */
void MoonPhaseDisplay::DrawCover(unsigned int moonDay)
{
	
	
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
