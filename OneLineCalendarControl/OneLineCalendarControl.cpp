/*
 * Copyright 2020, Alex Hitech <ahitech@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "OneLineCalendarControl.h"


BString ConvertNumberToHebew(unsigned char number)
{
	BString toReturn;
	
	switch(number)
	{
	case 1:
		toReturn = "א";
		break;
	case 2:
		toReturn = "ב";
		break;
	
		
	};
	
}


MonthView::MonthView(const char* name, float width, float height)
	: 	BMenu(name, width, height),
		nextYear(NULL),
		previousYear(NULL),
		nextMonth(NULL),
		previousMonth(NULL),
		currentYear(NULL),
		currentMonth(NULL)
{

	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.SetInsets(2)
		.Add	
	
}

MonthView::MonthView(BMessage* archive)
	: BMenu(archive)
{

	
}


MonthView::~MonthView()
{
	
}
