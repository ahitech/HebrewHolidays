#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <Rect.h>
#include <View.h>

#include "DateView.h"
#include "MoonPhase.h"
#include "hdate.h"

/*!
 *	\note	In case of error, all fields must be set to 0.
 */
typedef struct _gregorian_date {
	int mday;		// Day in the month, 1-31
	int mon; 		// Month, 1 = January
	int year;		// Year
} GregorianDate;



class MainView : public BView
{
	public:
		MainView(BRect frame);
//		MainView (BMessage* in);
		~MainView();

//		status_t Archive(BMessage* , bool deep = true) const;
//		static BArchivable* Instantiate (BMessage *);
		void GetPreferredSize(float *width, float* height);
//		void ResizeTo (float width, float height);
//		void ResizeBy (float width, float height);

		void Pulse ();
		bool CalculateHDate (void );

		hdate_struct* currentHDate;
		
		// The user must free the GregorianDate struct!
		GregorianDate* GetGregorianDate (hdate_struct const * );
		
		void UpdateAllFields(void);

	private:
		DateView* dateView;
		MoonPhaseDisplay *moonView;
		
		void NextHoliday();
		
};


#endif
