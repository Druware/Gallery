/*
 * Haiku Gallery - BOptionPopUp page.
 */
#ifndef OPTION_POP_UP_PAGE_H
#define OPTION_POP_UP_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BOptionPopUp;


class OptionPopUpPage : public GalleryPage {
public:
								OptionPopUpPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BOptionPopUp*		fPopUp;
			BCheckBox*			fEnabled;
			int32				fAdded;
};

#endif	// OPTION_POP_UP_PAGE_H
