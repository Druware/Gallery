/*
 * Haiku Gallery - BScrollView page.
 */
#ifndef SCROLL_VIEW_PAGE_H
#define SCROLL_VIEW_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BOptionPopUp;
class BScrollView;


class ScrollViewPage : public GalleryPage {
public:
								ScrollViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BScrollView*		fScroll;
			BOptionPopUp*		fBorder;
			BCheckBox*			fHighlight;
};

#endif	// SCROLL_VIEW_PAGE_H
