

#ifndef __CALENDAR_CONTROL_H__
#define __CALENDAR_CONTROL_H__

// System headers
#include <Control.h>
#include <RadioButton.h>
#include <String.h>
#include <StingView.h>

// Local headers
#include "hdate.h"


const uint32	GREGORIAN_SELECTED 	= 'GrSl';
const uint32	HEBREW_SELECTED		= 'HbSl';


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
		
		virtual void GetSelectedDate(void* out, enum DateRepresentingStructureFormat* );
		virtual void SetDate(const void* in, enum DateRepresentingStructureFormat* );
		
		virtual void AttachedToWindow();
		virtual status_t Archive(BMessage* out, bool deep = true);
		static CalendarControl* Instantiate(BMessage* in);
		const char*  Label() const;
		virtual void MessageReceived(BMessage *in);
		virtual void ResizeTo();
		virtual void SetEnabled(bool);
		virtual void SetLabel(const char* in);
		virtual bool IsEnabled(bool);
		
	protected:
		virtual void UpdateControl();
	
		// Data members
		BStringView	m_Label;		//!<	Label of the Calendar Control
		BStringView m_DateString;	//!<	Currently chosen date
		BRadioButton m_Gregorian;	//!<	Radio button for selecting Gregorian calendar
		BRadioButton m_Hebrew;		//!<	Radio button for selecting Hebrew calendar
};

#endif
