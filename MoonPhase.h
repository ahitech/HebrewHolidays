#ifndef MOONPHASE_H
#define MOONPHASE_H


#include <Bitmap.h>
#include <Rect.h>
#include <View.h>

#include "hdate.h"


// This class receives
class MoonPhaseDisplay : public BView
{
	public:
		MoonPhaseDisplay(BRect frame);
		~MoonPhaseDisplay();

//		void UpdateDisplay(hdate_struct* date);
		void AttachedToWindow();
		void Draw(BRect updateRect);
	private:
		BBitmap *picture;

};


#endif
