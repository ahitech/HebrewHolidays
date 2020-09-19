/*
 * Copyright 2020, Alex Hitech <ahitech@gmail.com>
 * All rights reserved. Distributed under the terms of the GPL license.
 */


#include "DaysLeftToNextHoliday.h"


/**
 *	\function	DaysLeftToNextHoliday::DaysLeftToNextHoliday()
 *	\brief		Default constructor.
 *	\details	It creates a square frame and then resizes itself to text
 *				that should be displayed.
 */
DaysLeftToNextHoliday::DaysLeftToNextHoliday()
	:	BStringView (BRect(0, 0, 30, 30),
					 "Next Holiday", "",
					 B_FOLLOW_H_CENTER | B_FOLLOW_TOP,
					 B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE)
{
	nextHoliday = new_hdate();
	toDisplay = COUNTDOWN;
}


/**
 *	\function	DaysLeftToNextHoliday::~DaysLeftToNextHoliday()
 *	\brief		Default destructor
 */
DaysLeftToNextHoliday::~DaysLeftToNextHoliday()
{
	RemoveSelf();
	delete_hdate (nextHoliday);
}



/**
 *	\function	void DaysLeftToNextHoliday::UpdateDay(const hdate_struct* in)
 *	\brief		Calculate the next holiday and update this info on screen
 *	\param[in]	in	The current hdate, from which the calculation is started.
 */
void DaysLeftToNextHoliday::UpdateDay(const hdate_struct* in)
{
	int holiday = 0;
	unsigned int counter = 0;
	char buffer[50] = { 0 };
	if (!in) return;		// Sanity check
	struct tm *tempTM = GetGregorianDate (in);
	hdate_struct* tempHDate = new_hdate();
	time_t	timeSinceEpoch;
	
	do
	{
		tempTM->tm_mday++;
		counter++;
		timeSinceEpoch = mktime(tempTM);
		hdate_set_gdate(tempHDate,
						tempTM->tm_mday,
						tempTM->tm_mon + 1,
						tempTM->tm_year + 1900);
		holiday = hdate_get_holyday (tempHDate, 1);		// Diaspora
		
	} while (holiday == 0);
	strftime (buffer,
			  49,
			  "%a, %D",
			  tempTM);
			  
/*			  
	printf ("Next holiday %d eve is in %d %s, on %s: %s\n",
			holiday,
			counter,
			counter > 1 ? "days" : "day",
			buffer,
			hdate_string (HDATE_STRING_HOLIDAY, holiday, HDATE_STRING_LONG, HDATE_STRING_LOCAL));
*/	
	UpdateString(timeSinceEpoch, counter, holiday, tempTM);
	delete_hdate (tempHDate);
	delete tempTM;	
}



/**
 *	\function 	void DaysLeftToNextHoliday::UpdateString(const time_t,
 *														int counter,
 *														int holiday)
 *	\brief		Updates the text countdown to the next holiday
 *	\param[in]	timeSinceEpoch	When the next holiday starts
 *	\param[in]	counter			Counter until the next holiday
 *	\param[in]	holiday			Holiday type (required to get name of the holiday)
 *	\param[in]	nextHolidayInGregorian	Next holiday's date in Gregorian calendar (can be NULL)
 */
void DaysLeftToNextHoliday::UpdateString(const time_t timeSinceEpoch,
										 const int counter,
										 const int holiday,
										 struct tm* nextHolidayInGregorian)
{
	BDateFormat format();	// Default locale
	BString		nextHolidayFromLibHdate;
	BString		stringToSet;
	char buffer[50];
	memset (buffer, ' ', 49);
	buffer[49] = '\0';
	
	nextHolidayFromLibHdate.SetTo(hdate_string (HDATE_STRING_HOLIDAY, 
												 holiday, 
												 HDATE_STRING_LONG,
												 HDATE_STRING_LOCAL));
												 
	nextHolidayFromLibHdate.ReplaceAll("_", " ");
			 
	switch (toDisplay)
	{
		case COUNTDOWN:
			stringToSet << nextHolidayFromLibHdate << " is in " << counter << ((counter > 1) ?  " days" : " day");
			break;
		case NEXT_HOLIDAY_ONLY:
			stringToSet << nextHolidayFromLibHdate;
			break;
		case NEXT_DATE_IN_GREGORIAN:
			if (nextHolidayInGregorian != NULL) {
				strftime (buffer,
								  49,
								  "%a, %D",
								  nextHolidayInGregorian);
				stringToSet << "Next holiday is on ";
			}
			stringToSet << buffer;
			break;
		case NEXT_DATE_IN_GREGORIAN_WITH_NAME:
			if (nextHolidayInGregorian != NULL) {
				strftime (buffer,
								  49,
								  "%a, %D",
								  nextHolidayInGregorian);
				stringToSet << nextHolidayFromLibHdate << " is on ";
			}
			stringToSet << buffer;
			break;
		case NONE:		// Intentional fall-through
		default:		// "Last item" falls here as well
			stringToSet.SetTo("                                                ");	// Empty string
	};
	this->SetText(stringToSet.String());
}



/**
 *	\function	void DaysLeftToNextHoliday::AttachedToWindow()
 *	\brief		Called when this view is attached to window.
 *	\details	Sets the background to the window's background.
 */
void DaysLeftToNextHoliday::AttachedToWindow()
{
	BView* parent = Parent();
	if (parent)
	{
		SetViewColor (parent->ViewColor());
	}
	BView::AttachedToWindow();
}



/**
 *	\function 	void DaysLeftToNextHoliday::GetPreferredSize (float* , float* );
 *	\brief		Reply with this view's preferred size.
 *	\param[out]	width	Preferred width of the window.
 *	\param[out]	height	Preferred height of the window.
 */
void DaysLeftToNextHoliday::GetPreferredSize (float *width, float *height)
{
	// Sanity check
	if (!width || !height)
	{
		return;
	}
	const char* text = this->Text();
	struct font_height fontHeight;
	*width = TEXT_MARGINS + this->StringWidth(text);

	this->GetFontHeight(&fontHeight);
	*height = fontHeight.ascent + fontHeight.descent + fontHeight.leading;
}



/**
 *	\function	struct tm* DaysLeftToNextHoliday::GetGregorianDate (const hdate_struct *in)
 *	\param[in]	in	Hebrew date for which the Gregorian date is returned.
 *	\returns	struct tm with the Gregorian date.
 *	\note		The caller must free the struct.
 */
struct tm* DaysLeftToNextHoliday::GetGregorianDate (const hdate_struct *in)
{
	if (!in)	return NULL;
	struct tm *toReturn = new struct tm();
	memset (toReturn, 0, sizeof (struct tm));
	if (toReturn) {
		toReturn->tm_mday = hdate_get_gday(in);
		toReturn->tm_mon  = hdate_get_gmonth (in) - 1;		// In struct tm, Jan is 0
		toReturn->tm_year = hdate_get_gyear (in) - 1900;	// In struct tm, years are from 1900
	}
	return toReturn;	
}


/**
 *	\function	void DaysLeftToNextHoliday::MouseDown(BPoint point)
 *	\param[in]		point	The position in which the user clicked
 *	\brief	This function changes the display of the View.
 */
 void DaysLeftToNextHoliday::MouseDown(BPoint point)
 {
 	printf ("ToDisplay was %d. ", this->toDisplay);
 	this->toDisplay = (enum DisplayedInfo)(this->toDisplay + 1);
 	if 	(this->toDisplay == LAST_ITEM_DONT_USE) {
 		this->toDisplay = NONE;
 	}
 	printf ("ToDisplay is %d.\n", this->toDisplay);
 	
 	// Call the base function of the class
	BStringView::MouseDown(point);
 } 
