/*
 * Haiku Gallery - BSlider page.
 */
#ifndef SLIDER_PAGE_H
#define SLIDER_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BOptionPopUp;
class BSlider;


class SliderPage : public GalleryPage {
public:
								SliderPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BSlider*			fSlider;
			BCheckBox*			fVertical;
			BOptionPopUp*		fHashMarks;
			BCheckBox*			fTriangle;
			BCheckBox*			fFill;
			BCheckBox*			fEnabled;
};

#endif	// SLIDER_PAGE_H
