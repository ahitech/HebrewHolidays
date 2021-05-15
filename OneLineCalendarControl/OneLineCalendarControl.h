/*
 * Copyright 2020, Alex Hitech <ahitech@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef __ONE_LINE_CALENDAR_CONTROL_H__
#define __ONE_LINE_CALENDAR_CONTROL_H__

#include <Control.h>
#include <SupportDefs.h>


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
