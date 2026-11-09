/*
 * Haiku Gallery - BButton page.
 */
#ifndef BUTTON_PAGE_H
#define BUTTON_PAGE_H

#include "GalleryPage.h"


class BButton;
class BCheckBox;
class BTextControl;


class ButtonPage : public GalleryPage {
public:
								ButtonPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BButton*			fButton;
			BButton*			fToggle;
			BCheckBox*			fEnabled;
			BTextControl*		fLabel;
			int32				fClicks;
};

#endif	// BUTTON_PAGE_H
