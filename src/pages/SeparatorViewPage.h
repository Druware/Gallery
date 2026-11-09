/*
 * Haiku Gallery - BSeparatorView page.
 */
#ifndef SEPARATOR_VIEW_PAGE_H
#define SEPARATOR_VIEW_PAGE_H

#include "GalleryPage.h"


class BOptionPopUp;
class BSeparatorView;
class BTextControl;


class SeparatorViewPage : public GalleryPage {
public:
								SeparatorViewPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BSeparatorView*		fSeparator;
			BTextControl*		fLabel;
			BOptionPopUp*		fBorder;
			BOptionPopUp*		fAlignment;
};

#endif	// SEPARATOR_VIEW_PAGE_H
