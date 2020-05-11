#include <InterfaceDefs.h>
#include <LayoutBuilder.h>

#include <stdio.h>

#include "MainView.h"

MainView::MainView (BRect frame)
	: BView(frame,
			"MainView",
			B_FOLLOW_ALL_SIDES,
			B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS | B_PULSE_NEEDED),
	  dateView (NULL),
	  currentHDate (NULL)
{
	float width, height;
	dateView = new DateView();
	currentHDate = new_hdate();

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	CalculateHDate();

	dateView->UpdateDay(currentHDate);

	moonView = new MoonPhaseDisplay();
	nextHolidayView = new DaysLeftToNextHoliday();

	BLayoutBuilder::Group<>(this, B_VERTICAL, TEXT_MARGINS)
		.SetExplicitAlignment(BAlignment(B_ALIGN_USE_FULL_WIDTH,
										 B_ALIGN_USE_FULL_HEIGHT))
		.SetExplicitMinSize(BSize(100, 110))
		.Add(dateView, 0.0f)
			.SetExplicitMinSize (BSize (100, 10))
			.SetExplicitAlignment (BAlignment (B_ALIGN_HORIZONTAL_CENTER,
											   B_ALIGN_BOTTOM))
		.Add(nextHolidayView, 0.0f)
			.SetExplicitMinSize (BSize (100, 10))
			.SetExplicitAlignment (BAlignment (B_ALIGN_HORIZONTAL_CENTER,
											   B_ALIGN_BOTTOM))
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

	delete_hdate (currentHDate);

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
//	if (dateView)
//	{
//		if (CalculateHDate())
			UpdateAllFields();
//	}
//	NextHoliday();
}


/**
 *	\function		void MainView::UpdateAllFields(void)
 *	\brief			This function is called when the hebrew date was changed.
 *					It causes the update of all fields of the main UI.
 */
void MainView::UpdateAllFields()
{
	dateView->UpdateDay(currentHDate);
	nextHolidayView->UpdateDay(currentHDate);
}



/*!
 *	\function	bool MainView::CalculateHDate (void)
 * 	\brief		This function turns to LibHDate in order to calculate Hebrew date,
 *	\returns	TRUE if the date was changed (after midnight), 
 *				FALSE otherwise.
 */
bool MainView::CalculateHDate (void)
{
	bool toReturn = false;
	time_t currentTime = time (NULL);
	hdate_struct* tempHDate = new_hdate();
	struct tm *today = localtime (&currentTime);
	hdate_set_gdate(tempHDate,
					today->tm_mday,
					today->tm_mon + 1,
					today->tm_year + 1900);	
					
	// Now we have two Hebrew dates; the previous one is in this->currentHDate,
	// and the current one is in tempHDay. We will compare them and update in
	// case it's necessary.
	if (currentHDate && tempHDate &&
		(tempHDate->hd_day != this->currentHDate->hd_day ||
		 tempHDate->hd_mon != this->currentHDate->hd_mon ||
		 tempHDate->hd_year!= this->currentHDate->hd_year))
	{
		hdate_set_hdate(currentHDate, 
						tempHDate->hd_day,
						tempHDate->hd_mon,
						tempHDate->hd_year);
		toReturn = true;
	}
	delete_hdate (tempHDate);
	return toReturn;
}




/*!
 *	\function 		GregorianDate* MainView::GetGregorianDate (hdate_struct* )
 *	\brief			Calculate gregorian date for a hebrew date
 *	\param[in]		in		Hebrew date (const)
 *	\returns		An allocated struct for gregorian date.
 *					NULL in case of no available memory or invalid input.
 *					The fields will be 0 in case of error.
 *	\note			The caller must free the memory allocated by the returned struct.
 */
GregorianDate* MainView::GetGregorianDate (hdate_struct const *in)
{
	GregorianDate* toReturn;
	
	// Sanity check
	if (!in) return NULL;
	
	toReturn = new GregorianDate;
	
	if (toReturn) {
		toReturn->mday = hdate_get_gday(in);
		toReturn->mon  = hdate_get_gmonth (in);
		toReturn->year = hdate_get_gyear (in);
	}
	return toReturn;
}


void MainView::NextHoliday()
{
	int holiday;
	unsigned int counter = 0;
	time_t currentTime = time (NULL);
	hdate_struct* inTest = new_hdate();
	do
	{
		currentTime += (60 * 60 * 24);
		counter++;
		struct tm *today = localtime (&currentTime);
		hdate_set_gdate(inTest,
						today->tm_mday,
						today->tm_mon + 1,
						today->tm_year + 1900);
		holiday = hdate_get_holyday (inTest, 1);		// Diaspora
		
	}
	while (holiday == 0);
//	printf ("Next holiday is in %d days: %s\n",
//			counter,
//			hdate_string (HDATE_STRING_HOLIDAY, holiday, HDATE_STRING_LONG, HDATE_STRING_LOCAL));
	delete_hdate(inTest);
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
