/*
 * Copyright 2018, Alex Hitech <ahitech@gmail.com>
 * All rights reserved. Distributed under the terms of the GPL license.
 */
#ifndef __DAYS_LEFT_TO_NEXT_HOLIDAY_H__
#define __DAYS_LEFT_TO_NEXT_HOLIDAY_H__

#include <DateFormat.h>
#include <StringView.h>
#include <SupportDefs.h>
#include <time.h>
#include <stdio.h>
#include <cstring>


#include "hdate.h"
#include "MainView.h"

enum DisplayedInfo {
	NONE = 0
	,NEXT_DATE_IN_GREGORIAN = 1
	,NEXT_DATE_IN_GREGORIAN_WITH_NAME
	,COUNTDOWN
	,NEXT_HOLIDAY_ONLY
	,LAST_ITEM_DONT_USE
};
	


class DaysLeftToNextHoliday :
	public BStringView
{
public:
	DaysLeftToNextHoliday();
	~DaysLeftToNextHoliday();
	
	void UpdateDay (const hdate_struct *);
	virtual void GetPreferredSize (float *width, float *height);
	virtual void AttachedToWindow ();
	virtual void MouseDown (BPoint point);
protected:
	unsigned const char TEXT_MARGINGS = 5;
	hdate_struct*	nextHoliday;
	
	struct tm* GetGregorianDate (const hdate_struct *);
	void UpdateString(const time_t timeSinceEpoch,
					  const int counter,
					  const int holiday,
					  struct tm* nextHolidayInGregorian = NULL);
	enum DisplayedInfo	toDisplay;
};


#endif // __DAYS_LEFT_TO_NEXT_HOLIDAY_H__
