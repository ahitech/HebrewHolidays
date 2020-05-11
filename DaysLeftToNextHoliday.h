/*
 * Copyright 2018, Alex Hitech <ahitech@gmail.com>
 * All rights reserved. Distributed under the terms of the GPL license.
 */
#ifndef __DAYS_LEFT_TO_NEXT_HOLIDAY_H__
#define __DAYS_LEFT_TO_NEXT_HOLIDAY_H__

#include <StringView.h>
#include <SupportDefs.h>
#include <time.h>
#include <stdio.h>
#include <cstring>


#include "hdate.h"
#include "MainView.h"


class DaysLeftToNextHoliday :
	public BStringView
{
public:
	DaysLeftToNextHoliday();
	~DaysLeftToNextHoliday();
	
	void UpdateDay (const hdate_struct *);
	void GetPreferredSize (float *width, float *height);
	void AttachedToWindow ();
protected:
	unsigned const char TEXT_MARGINGS = 5;
	hdate_struct*	nextHoliday;
	
	struct tm* GetGregorianDate (const hdate_struct *);
};


#endif // __DAYS_LEFT_TO_NEXT_HOLIDAY_H__
