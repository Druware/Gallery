/*
 * Haiku Gallery - BPopUpMenu page.
 */
#ifndef POP_UP_MENU_PAGE_H
#define POP_UP_MENU_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class PopUpArea;


class PopUpMenuPage : public GalleryPage {
public:
								PopUpMenuPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			PopUpArea*			fArea;
			BCheckBox*			fDisabledItem;
};

#endif	// POP_UP_MENU_PAGE_H
