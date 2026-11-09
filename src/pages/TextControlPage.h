/*
 * Haiku Gallery - BTextControl page.
 */
#ifndef TEXT_CONTROL_PAGE_H
#define TEXT_CONTROL_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BTextControl;


class TextControlPage : public GalleryPage {
public:
								TextControlPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BTextControl*		fName;
			BTextControl*		fPassword;
			BCheckBox*			fEnabled;
			BCheckBox*			fInvalid;
			BCheckBox*			fHideTyping;
};

#endif	// TEXT_CONTROL_PAGE_H
