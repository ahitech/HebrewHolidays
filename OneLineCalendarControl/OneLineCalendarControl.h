/*
 * Copyright 2020, Alex Hitech <ahitech@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef __ONE_LINE_CALENDAR_CONTROL_H__
#define __ONE_LINE_CALENDAR_CONTROL_H__

#include <Control.h>
#include <Menu.h>
#include <String.h>
#include <SupportDefs.h>


BString ConvertNumberToHebew(unsigned char number);


class MonthView
	: public BMenu
{
public:
	MonthView(const char* name, float width, float height);
	MonthView(BMessage* archive);
	virtual ~MonthView();
	
	virtual status_t Archive(BMessage* archive, bool deep = true);
	
protected:
	BString dayNames[31],
			monthNames[13],
			yearNames[11];
			
	BButton*	nextYear,
				previousYear,
				nextMonth,
				previousMonth;
				
	BStringView*	currentYear,
					currentMonth;
}


class OneLineCalendarControl
	: public BControl
{
public:
	OneLineCalendarControl (BRect,
							const char *name,
							const char *label,
							BMessage* message,
							uint32 resizingMode,
							uint32 flags);
	OneLineCalendarControl(BMessage* archive);
	virtual ~OneLineCalendarControl();							
	
	virtual void AttachedToWindow();

private:
	

};


#endif // __ONE_LINE_CALENDAR_CONTROL_H__
