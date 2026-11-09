/*
 * Haiku Gallery - BMenuField page.
 */
#ifndef MENU_FIELD_PAGE_H
#define MENU_FIELD_PAGE_H

#include "GalleryPage.h"


class BCheckBox;
class BMenuField;
class BTextControl;


class MenuFieldPage : public GalleryPage {
public:
								MenuFieldPage();

	virtual	const char*			Title() const;
	virtual	const char*			Description() const;
	virtual	const char*			SourceSnippet() const;
	virtual	bool				HandleMessage(BMessage* message);

protected:
	virtual	BView*				CreateSample();
	virtual	BView*				CreateOptions();

private:
			BMenuField*			fField;
			BCheckBox*			fEnabled;
			BTextControl*		fLabel;
};

#endif	// MENU_FIELD_PAGE_H
