

#include "CalendarControl.h"



#define 	BUTTON_WIDTH	30
#define		SPACING			4

	/*!	\details	Defines number of years before and after selected year in the 
	 *				years menu.
	 */
#define		YEARS_UP_AND_DOWN	5

rgb_color weekdayNameColor = {0x80, 0x80, 0x80, 255};
rgb_color weekendNameColor = {255, 0x80, 0x80, 255};
rgb_color weekendDateColor = {255, 0x0, 0x0, 255};
rgb_color todayBackColor = {0, 0, 0x80, 255};


/*!	\brief		Constructor.
 *	\details	It performs initial division of the control's frame to three
 *				parts in order to display date, month and year.
 *	\param[in]	frame			The outer bounds of the control.
 *	\param[in]	name			Name of the control.
 *	\param[in]	labelInForCalendar		The label of the calendar part of control.
 *	\param[in]	dateRepresentingStruct	Pointer to the structure that represents the date.
 *										Can be either "struct tm" or "struct hdate".
 *	\param[in]	formatIn				Defines the format of the structure passed above.
 *	\param[in]	toSend					Message sent when the control's value is changed.
 *	\attention		It's assumed that calendar modules were already initialized prior
 *						to calling this function.
 */
CalendarControl::CalendarControl  ( BRect 	frame,
									const 	char* name,
									const 	char* labelInForCalendar,
									void*	dateRepresentingStructure,
									enum DateRepresentingStructureFormat formatIn,
									BMessage* message,
									uint32 	resizingMode,
									uint32	flags)
	: BControl (frame, name, label, message, resizingMode, flags)
{
	
	
	
}
// <-- end of constructor from set of values



/**	\brief		Constructor from BMessage.
 *	\details	
 *	\param[in]	in	BMessage with archive of the control.
 */
CalendarControl::CalendarControl(BMessage* in)
	: BControl(in)
{
	
}



/*!	\brief	Destructor
 */
CalendarControl::~CalendarControl()
{
	
}



/*!	\brief	Obtain and use parent's values for background and foreground colors etc.
 */
void CalendarControl::AttachedToWindow()
{
	// Get the view color of the father
	if ( Parent() ) {
		SetViewColor( Parent()->ViewColor() );
	}
	// Attach to window both current view and all of its children
	BControl::AttachedToWindow();
	
	// This view should respond to the messages - thus the Looper must know it
	BLooper* looper = ( BLooper* )Looper();
	if (looper && 
		looper->LockLooper() ) 
	{
		looper->AddHandler((BHandler* )this );
		looper->UnlockLooper();
	}
	
	UpdateTargets(fDateSelector);
	
	this->InvalidateLayout();
//	this->Relayout();
	this->Invalidate();
}
