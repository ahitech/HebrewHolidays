#include <Application.h>
#include <File.h>
#include <Resources.h>
#include <Roster.h>
#include <TranslationUtils.h>


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
		picture = (BBitmap *)res.LoadResource((uint32)'PNG ', "Moon", &size);
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

	// Add it as the background of current view
	if (picture != NULL)
	{
		DrawBitmap (picture);
	}
}
