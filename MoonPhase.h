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
		MoonPhaseDisplay();
		~MoonPhaseDisplay();

//		void UpdateDisplay(hdate_struct* date);
		void AttachedToWindow();
		void Draw(BRect updateRect);
		void GetPreferredSize (float *width, float *height);
		void ResizeTo (float width, float height);
		void ResizeBy (float , float );
	private:
		BBitmap *picture;

};


#endif
