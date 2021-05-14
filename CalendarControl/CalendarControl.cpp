

#include "CalendarControl.h"

#undef 	B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "CalendarControl"




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
	m_Label = new BStingView(BRect (0, 0, 1, 1),
							 "label",
							 labelInForCalendar);
	m_Gregorian = new BRadioButton (BRect(0, 0, 1, 1),
									"gregorian radio",
									B_TRANSLATE("Gregorian"),
									new BMessage(GREGORIAN_SELECTED));
	m_Hebrew = new BRadioButton (BRect(0, 0, 1, 1),
								 "hebrew radio",
								 B_TRANSLATE("Hebrew"),
								 new BMessage(HEBREW_SELECTED));
	
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.SetInsets(5)
		.Add(m_Label)
		.AddGroup(B_HORIZONTAL)
			.SetInsets(2)
			.Add(m_DateString)
			.Add(<<MENU BUTTON>>)
		.End()	
		.Add(fDataView)
		.Add(fCloseButton)
	.Layout();
	
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
	if (m_Label) {
		m_Label->RemoveSelf();
		delete m_Label;
		m_Label = NULL;
	}
	
}



/*!	\brief		Function that handles internal messages
 *	\details
 *	\param[in]	in	BMessage that was sent to internal loopen
 */
void CalendarControl::MessageReceived (BMessage in)
{
	if (!in)	return;			// Sanity check
	switch (in->what)
	{
		case GREGORIAN_SELECTED:
			break;
		case HEBREW_SELECTED:
			break;
		default:
			// If nothing helps, kick the problem to the base class :)
			BControl::MessageReceived(in);
			break;
	};	// <-- end of "switch (message constant)"
}
// <-- end of function CalendarControl::MessageReceived()



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



/*!	\brief		Set the new label for the control.
 *	\param[in]	in	New label to be set
 */
void CalendarControl::SetLabel(const char* in) {
	if (in)
	{
		m_Label.SetText(in);
		Invalidate();	
	}	
}	// <-- end of function CalendarControl::SetLabel(const char *)



/*!	\brief		Update the overall look of the Calendar Control.
 */
void CalendarControl::UpdateControl()
{
	this->Invalidate();
}
// <-- end of function CalendarControl::UpdateControl()
