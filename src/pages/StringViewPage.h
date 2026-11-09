/*
 * Haiku Gallery - BStringView page.
 */
#ifndef STRING_VIEW_PAGE_H
#define STRING_VIEW_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BOptionPopUp;
class BStringView;
class BTextControl;


class StringViewPage : public GalleryPage {
public:
								StringViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BStringView*		fString;
			BTextControl*		fText;
			BOptionPopUp*		fAlignment;
			BOptionPopUp*		fTruncation;
			BCheckBox*			fBold;
};

#endif	// STRING_VIEW_PAGE_H
