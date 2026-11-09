/*
 * Haiku Gallery - BColorControl page.
 */
#ifndef COLOR_CONTROL_PAGE_H
#define COLOR_CONTROL_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BColorControl;
class BOptionPopUp;


class ColorControlPage : public GalleryPage {
public:
								ColorControlPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			void				_UpdateSwatch();

			BColorControl*		fColor;
			BView*				fSwatch;
			BOptionPopUp*		fLayout;
			BOptionPopUp*		fCellSize;
			BCheckBox*			fEnabled;
};

#endif	// COLOR_CONTROL_PAGE_H
