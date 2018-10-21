#include <Application.h>
#include <File.h>
#include <Resources.h>
#include <Roster.h>
#include <TranslationUtils.h>
#include <TranslatorFormats.h>
#include <stdio.h>


#include "MoonPhase.h"

MoonPhaseDisplay::MoonPhaseDisplay (BRect frame)
	:	BView (frame, "MoonPhaseDisplay",
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
//		picture = (BBitmap *)res.LoadResource((uint32)'PNG ', "logo", &size);
//		printf ("Successfully loaded picture in size of %d!\n", size);
//		printf ("Its validity is %s, pointer is 0x%08X!\n", (picture->IsValid() ? "valid" : "not valid"));
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
}

void MoonPhaseDisplay::Draw(BRect updateRect)
{
	BView::Draw(updateRect);

	// Add it as the background of current view
	if (picture != NULL)
	{
		SetHighColor(255, 0, 0);
		StrokeRect(Bounds());

		DrawBitmap (picture, Bounds());
//		printf ("In DRAW!\n");
	}
}
