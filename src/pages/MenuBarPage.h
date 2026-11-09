/*
 * Haiku Gallery - BMenuBar, BMenu and BMenuItem page.
 */
#ifndef MENU_BAR_PAGE_H
#define MENU_BAR_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BMenu;


class MenuBarPage : public GalleryPage {
public:
								MenuBarPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BMenu*				fEditMenu;
			BCheckBox*			fEditEnabled;
};

#endif	// MENU_BAR_PAGE_H
