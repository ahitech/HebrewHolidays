#ifndef DATEVIEW_H
#define DATEVIEW_H

#include <StringView.h>
#include "hdate.h"

unsigned const char TEXT_MARGINS = 0;	// 0 pixels from each side

class DateView : public BStringView
{
	public:
		DateView ();
		~DateView ();

		void UpdateDay(hdate_struct* currentDay);
		void GetPreferredSize(float *width, float *height);
		void AttachedToWindow();

	private:

		hdate_struct* currentDay;


};	// <-- end of class DateView


#endif
