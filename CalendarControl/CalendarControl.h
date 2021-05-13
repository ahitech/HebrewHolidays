

#ifndef __CALENDAR_CONTROL_H__
#define __CALENDAR_CONTROL_H__

#include <Control.h>


/*!	\brief		Enum that represents in which format does the CalendarControl
 *				receive the date passed to it as a parameter.
 *	\details	Currently it supports only two formats, "struct tm" for
 *				Gregorian date and "struct hdate" for Hebrew date.
 */
enum DateRepresentingStructureFormat {
	 GREGORIAN_STRUCT_TM = 1
	,HEBREW_DATE = 2
	,LAST_OPTION_DONT_USE 
}



class CalendarControl
	: public BControl
{
	public:
		CalendarControl (BRect frame,
				         const char* name,
				         const char* label,
						 void*	dateRepresentingStructure,
						 enum DateRepresentingStructureFormat formatIn,
				         BMessage* message,
				         uint32 resizingMode,
				         uint32 flags);
		CalendarControl (BMessage* archive);
		
		virtual CalendarControl();
		
		virtual void AttachedToWindow();
		virtual void MessageReceived(BMessage *in);
		virtual void SetEnabled(bool);
		virtual bool IsEnabled(bool);
	protected:
		
};

#endif
