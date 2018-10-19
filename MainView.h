#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <Rect.h>
#include <View.h>

#include "DateView.h"
#include "MoonPhase.h"

class MainView : public BView
{
	public:
		MainView(BRect frame);
//		MainView (BMessage* in);
		~MainView();

//		status_t Archive(BMessage* , bool deep = true) const;
//		static BArchivable* Instantiate (BMessage *);
		void GetPreferredSize(float *width, float* height);

	private:
		DateView* dateView;
		MoonPhaseDisplay *moonView;
};


#endif
